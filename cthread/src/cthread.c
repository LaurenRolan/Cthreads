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

	t = malloc(sizeof(TCB_t));
	t->ticket = prio;
	esc->tidCounter = esc->tidCounter + 1;
	t->tid = esc->tidCounter;
	t->state = PROCST_CRIACAO;

	getcontext(&(t->context));
	t->context.uc_stack.ss_sp = (char *) malloc(SIGSTKSZ);
	t->context.uc_stack.ss_size = SIGSTKSZ;
	t->context.uc_link = &(esc->terminate);

	makecontext(&(t->context), (void (*)(void))start, 1, arg);
	
	if(put_aptos(t) != 0)
		return ERRO;
	
	return t->tid;

}

int csetprio(int tid, int prio){
	
	TCB_t *t;
	
	if(prio < 0 || prio > 3)
		return ERRO;

	t = search_thread(tid);
	if(t == NULL)
		return ERRO;	

	t->ticket = prio;

	return SUCESSO;

}

int csem_init(csem_t *sem, int count){ //Não funciona como deveria
    
	//biblioteca ainda não inicializada	
	if(esc == NULL)
		init_lib();	

	sem->fila = (PFILA2) malloc(sizeof(PFILA2));
	sem->count = count;
	if(AppendFila2(esc->semaforos, (void*) sem) != 0){
        	return ERRO;
	}
	return SUCESSO;
}

int cyield(){
	TCB_t * TCB;
	TCB = esc->executando;
	put_aptos(TCB);
	return dispatcher();
}

int cjoin(int tid){
	TCB_t *TCB, *thread;
  	blocked* b;
	int controle = 1;
	
	TCB = esc->executando;
	TCB->state = PROCST_BLOQ;
	b = (blocked*) malloc(sizeof(blocked));
	b->tcb = TCB;
	b->tid = tid;
	AppendFila2(esc->bloq_join, (void *) b);
  	//procurar por thread nas estruturas disponíveis ---> TCB_t *searchThread(int tid)
	thread = search_thread(tid);
	getcontext(thread->context.uc_link);
  
  	if(controle == 1){
      		controle = 0;
		return dispatcher();
    	}
    	else{
      		//thread 'tid' terminou
		//coloca thread bloqueada nos aptos		
		put_aptos(TCB);
		//faz processos de término da função anteriormente executando
		thread->state = PROCST_TERMINO;
		//desalocar a stack do processo
		free(thread->context.uc_stack.ss_sp);
		//desalocar TCB 
		free (thread);	

/********TIRAR DO BLOQUEADO*****/
		
		
		esc->executando = NULL;

      		return dispatcher();
  	}
}

int cwait(csem_t *sem){ //não testada
    	if(sem->count > 0) {
		sem->count --;
		return SUCESSO;
	}
	if(AppendFila2(sem->fila,(void *) esc->executando) != 0) {
		printf("Erro ao inserir na fila de bloqueados.\n");
		return ERRO;
	}
	esc->executando->state = PROCST_BLOQ;
	if(dispatcher() != ERRO) return SUCESSO;
	return ERRO;
}

int csignal(csem_t *sem){
	csem_t *atual;
	int achou = 0;
	//Biblioteca não inicializada, não há semáforo algum.
    	if(esc==NULL) return ERRO;
	
	//Verifica o primeiro da fila
	FirstFila2(esc->semaforos);
	atual = (csem_t*) GetAtIteratorFila2(esc->semaforos);
	while(achou != 1 && atual != NULL){
		if(atual == sem) {
			//Pega a 1ª thread da fila do semáforo e a põe em aptos
			FirstFila2(sem->fila);
			if(put_aptos((TCB_t*)GetAtIteratorFila2(sem->fila))!=SUCESSO)
				printf("Erro ao inserir a thread em aptos.\n");
			DeleteAtIteratorFila2(sem->fila);
			sem->count ++;
			achou = 1;
		}
		else {
			//Passa para o próximo da fila
			NextFila2(esc->semaforos);
			atual = (csem_t*) GetAtIteratorFila2(esc->semaforos);
		}
	}
	if(achou!=1) {
		printf("Semaforo inserido nao existe.\n");
		return ERRO;
	}
	return SUCESSO;
}

int cidentify (char *name, int size){

	char *str = "\tLauren Silva Rolan Sampaio - 00262517\n\tLeonardo da Luz Dorneles - 00262516\n\tNatalia Gubiani Rampon - 00262512\n";

	//biblioteca ainda não inicializada
	if(esc == NULL)
		init_lib();

	if(size < 0)
		return ERRO;


	memcpy(name, str, size);

	if(size == 0)
		name[0] = '\0';
	else
		name[size-1] = '\0';

	return SUCESSO;
}
