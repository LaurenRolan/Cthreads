#include "escalonador.h"
#include "cthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

escalonador* esc;

int ccreate (void* (*start)(void*), void *arg, int prio){

	//biblioteca ainda não inicializada
	if(esc == NULL)
		init_lib();

	TCB_t* t;	

	//Alocando e inicializando TCB
	t = malloc(sizeof(TCB_t));
	
	if(t == NULL)
		return ERRO;
	
	t->ticket = prio;
	esc->tidCounter = esc->tidCounter + 1;
	t->tid = esc->tidCounter;
	t->state = PROCST_CRIACAO;

	//Inicializando funcao de término de thread
	getcontext(&(t->context));
	t->context.uc_stack.ss_sp = (char *) malloc(SIGSTKSZ);
	t->context.uc_stack.ss_size = SIGSTKSZ;
	t->context.uc_link = &(esc->terminate);

	makecontext(&(t->context), (void (*)(void))start, 1, arg);
	
	//Por fim, poe ela na fila de aptos
	if(put_aptos(t) != 0)
		return ERRO;
	
	return t->tid;
}

int csetprio(int tid, int prio){
	
	TCB_t *t, *search;

	//Biblioteca ainda nao inicializada
	if(esc == NULL)
		init_lib();
	
	//Prioridade inválida
	if(prio < 0 || prio > 3)
		return ERRO;

	//Procura a thread que quer modificar
	t = search_thread(tid);
	if(t == NULL)
		return ERRO;	

	//se a thread esta na fila de aptos, tem que trocar ela para uma outra fila correspondente à sua prio
	if(t->state == PROCST_APTO){
		
		//primeiramente iremos tira-la da fila de aptos antiga	
		if(FirstFila2(esc->aptos[t->ticket]) != 0) 
			return ERRO;			//Essa fila de prioridade está vazia e não devia estar
		do{
			search = (TCB_t*) GetAtIteratorFila2(esc->aptos[t->ticket]);
			
			//se encontrou a thread, tem que deletar ela da fila antiga
			if(search->tid == tid){
				if(DeleteAtIteratorFila2(esc->aptos[t->ticket]) != 0)
					return ERRO;
				break;	
			}
		}while(!NextFila2(esc->aptos[t->ticket]));
		
		//Muda prioridade da thread
		t->ticket = prio;
		
		//E poe ela na nova fila de aptos
		put_aptos(t);
	}
	else
		t->ticket = prio;

	return SUCESSO;

}

int csem_init(csem_t *sem, int count){
	//biblioteca ainda não inicializada	
	if(esc == NULL)
		init_lib();
	//Aloca espaço para fila e atribui contador
	sem->fila = (PFILA2) malloc(sizeof(PFILA2));
	if(CreateFila2(sem->fila)!=SUCESSO) return ERRO;
	sem->count = count;
	
	//Adiciona semáforo à lista do escalonador
	if(AppendFila2(esc->semaforos, (void*) sem) != 0){
        	return ERRO;
	}
	return SUCESSO;
}

int cyield(){
	
	//Biblioteca ainda nao inicializada
	if(esc == NULL)
		init_lib();
	
	TCB_t * TCB;

	//Poe a thread que estava executando em aptos
	TCB = esc->executando;
	put_aptos(TCB);

	//E por fim chama o dispatcher
	return dispatcher();
}

int cjoin(int tid){
	TCB_t *TCB, *thread;
  	blocked* b;	

	//Biblioteca ainda nao inicializada	
	if(esc == NULL)
		init_lib();
	
	//procurar por thread nas estruturas disponíveis ---> TCB_t *searchThread(int tid)
	thread = search_thread(tid);
	
	//Se a thread tentou esperar por ela mesma terminar ela nunca ira ser desbloqueada
	//Logo isso acarreta em erro
	if(esc->executando->tid == tid){
		printf("A thread %d esta esperando por ela mesmo para terminar\n", tid);
		return -1;
	}

	//Se a thread procurada existe e nao tem mais nenhuma thread sendo bloqueada por ela
	if(thread != NULL && !has_blocked_by(tid)){
		TCB = esc->executando;
		TCB->state = PROCST_BLOQ;
		b = (blocked*) malloc(sizeof(blocked));
	
		if(b == NULL)
			return ERRO;

		//Coloca thread na fila de bloqueados, estando bloqueada por 'tid'
		b->tcb = TCB;
		b->tid = tid;		
		AppendFila2(esc->bloq_join, (void *) b);
	  
		//Muda a funcao de termino para a funcao de termino por join		
		getcontext(thread->context.uc_link);
		thread->context.uc_link->uc_stack.ss_sp = (char *)  malloc(SIGSTKSZ);
		thread->context.uc_link->uc_stack.ss_size = SIGSTKSZ;
		thread->context.uc_link->uc_link = NULL;
		makecontext(thread->context.uc_link, (void (*)(void))terminate_join, 0);
		
		return dispatcher(); 
	}
	else return ERRO;
}


int cwait(csem_t *sem){
	//Biblioteca não inicializada, não há semáforo algum.
	if(esc == NULL) {
		init_lib();
		return ERRO;
	}
	
	//Não existe esse escalonador
	if(sem == NULL) return ERRO;
	
	//Se houver recursos, apenas decrementa
    	if(sem->count > 0) {
		sem->count --;
		return SUCESSO;
	}
	
	//Se não houver recursos, adiciona à lista de bloqueados do semáforo e decrementa
	if(AppendFila2(sem->fila,(void *) esc->executando) != 0) {
		printf("Erro ao inserir na fila de bloqueados.\n");
		return ERRO;
	}
	sem->count --;
	
	//Transforma a thread em bloqueada e chaveia de contexto
	esc->executando->state = PROCST_BLOQ;
	if(dispatcher() != ERRO) return SUCESSO;
	return ERRO;
}

int csignal(csem_t *sem){
	csem_t *atual;
	int achou = 0;
	
	//Biblioteca não inicializada, não há semáforo algum.
    	if(esc==NULL)  {
		init_lib();
		return ERRO;
	}
	
	//Semáforo não foi alocado
	if(sem==NULL) return ERRO;
	
	//Verifica o primeiro da fila
	FirstFila2(esc->semaforos);
	atual = (csem_t*) GetAtIteratorFila2(esc->semaforos);
	
	while(achou != 1 && atual != NULL){
		if(atual == sem) { //Se o semáforo estiver na lista do escalonador
			//Pega a 1ª thread da fila do semáforo (se houver) e a põe em aptos
			if(FirstFila2(sem->fila) == SUCESSO) {
				if(put_aptos((TCB_t*)GetAtIteratorFila2(sem->fila))!=SUCESSO)
					printf("Erro ao inserir a thread em aptos.\n");
				DeleteAtIteratorFila2(sem->fila);
			}
			//Libera o recurso
			sem->count ++;
			achou = 1;
		}
		else {
			//Passa para o próximo da fila
			NextFila2(esc->semaforos);
			atual = (csem_t*) GetAtIteratorFila2(esc->semaforos);
		}
	}
	//Se o semáforo não estiver na lista do escalonador
	if(achou!=1) {
		printf("Semaforo inserido nao existe.\n");
		return ERRO;
	}
	return SUCESSO;
}

int cidentify (char *name, int size){

	char *str = "\tLauren Silva Rolan Sampaio - 00262517\n\tLeonardo da Luz Dorneles - 00262516\n\tNatalia Gubiani Rampon - 00262502\n";

	//biblioteca ainda não inicializada
	if(esc == NULL)
		init_lib();

	// Nao pode-se copiar um numero negativo de caracteres
	if(size < 0)
		return ERRO;

	//Copia string para name
	memcpy(name, str, size);

	//Coloca sinalizacao de final de string
	if(size == 0)
		name[0] = '\0';
	else
		name[size-1] = '\0';

	return SUCESSO;
}
