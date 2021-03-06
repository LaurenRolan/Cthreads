#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include "escalonador.h"

escalonador* esc;

/* Inicializa a estrutura necessaria ao escalonador */
int init_escalonador(){
	int i;

	//Se o escalonador nao foi inicializado ainda
	if(esc == NULL){
		esc = (escalonador *) malloc(sizeof(escalonador));

		if(esc == NULL)
			return ERRO;
	
		esc->bloq_join = (PFILA2) malloc(sizeof(PFILA2));
		esc->semaforos = (PFILA2) malloc(sizeof(PFILA2));
		esc->tidCounter = 0;
	
		//Cria contexto de termino de funcoes	
		getcontext(&(esc->terminate));
		esc->terminate.uc_stack.ss_sp = (char *)  malloc(SIGSTKSZ);
		esc->terminate.uc_stack.ss_size = SIGSTKSZ;
		esc->terminate.uc_link = NULL;
		makecontext(&(esc->terminate), (void (*)(void))terminate_thread, 0);
		
		for(i = 0; i < PRIORIDADES; i++)
			esc->aptos[i] = malloc(sizeof(PFILA2));
	
		if(CreateFila2(esc->bloq_join) != 0)
			return ERRO;
		if(CreateFila2(esc->semaforos) != 0)
			return ERRO;
		for(i = 0; i < PRIORIDADES; i++)
			if(CreateFila2(esc->aptos[i]) != 0)
				return ERRO;
	}

	return SUCESSO;

}

/* Poe  uma thread na fila de aptos correspondente à sua prioridade */
int put_aptos(TCB_t* newThread){

	if(newThread == NULL){
		printf("Estrutura recebida para insercao na fila de aptos tem valor %p\n", newThread);
		return ERRO;
	}
	else{
		newThread->state = PROCST_APTO;

		if(AppendFila2(esc->aptos[newThread->ticket], (void *)newThread) != 0){
			printf("Erro na insercao de %p na fila de aptos\n", newThread);
			return ERRO;
		}
	}
	
	return SUCESSO;
}

/* Dispatcher é responsável por escolher qual a próxima thread que irá executar */
int dispatcher(){
	
	int i, erro;
	TCB_t* temp;
	TCB_t* atual;
	atual = esc->executando;	

	//Passa por todas filas de aptos, da prioridade 0 a 3, procurando pela primeira thread disponível
	for(i=0; i < PRIORIDADES; i++){
		if(FirstFila2(esc->aptos[i]) != 0 && LastFila2(esc->aptos[i]) != 0)	//Verifica se a fila é vazia	
			continue;

		if(( temp = (TCB_t*) GetAtIteratorFila2(esc->aptos[i]) ) && temp != NULL){
			temp->state = PROCST_EXEC;
			//retira processo da fila de aptos
			DeleteAtIteratorFila2(esc->aptos[i]);
			esc->executando = temp;
			if(atual != NULL){
				//dispatcher foi chamado por yield, wait
				erro = swapcontext(&(atual->context),&(temp->context));
				if(erro  == -1){
					fprintf(stderr, "Erro ao mudar de contexto no dispatcher. Thread ID %d \n", temp->tid);
					return ERRO;
				}
			}
			else{		
				//dispatcher foi chamado de dentro da terminate_thread, logo nao ha processo executando
				//para fazer swap				
				if(setcontext(&(temp->context)) == -1){
					fprintf(stderr, "Erro ao mudar de contexto no dispatcher. Thread ID %d \n", temp->tid);
					return ERRO;
				}
			}	
			return SUCESSO;
		}
	}
		
	return ERRO; //não existe nenhuma thread apta no momento
}

/*Função executada na primeira chamada à biblioteca*/
int init_lib() {
	//Se já existe um escalonador, não é necessário inicializar a biblioteca
	if (esc != NULL) return ERRO;
	
	//Aloca e cria contexto da main, seguindo as definições do enunciado
	TCB_t *tmain;
	tmain = malloc(sizeof(TCB_t));
	tmain->ticket = 0;
	tmain->state = PROCST_EXEC;
	tmain->tid = 0; 
	getcontext(&(tmain->context));
	
	//Inicializa o escalonador
	if(init_escalonador()!= SUCESSO) return ERRO;
	
	//Põe a main em execução
	esc->executando = tmain;
	return SUCESSO;
	
}

void terminate_thread(){

	esc->executando->state = PROCST_TERMINO;
	
	//atualiza contexto, para próxima vez que vierem pra cá
	getcontext(&(esc->terminate));

	//desalocar a stack do processo
	free(esc->executando->context.uc_stack.ss_sp);

	//desalocar TCB 
	free (esc->executando);	

	//Retira thread do executando
	esc->executando = NULL;

	dispatcher();
	return;
}

TCB_t* search_thread(int tid){

	int i;	
	TCB_t *t;
	csem_t* s;
	blocked *b;

	// Primeiro vê se essa thread é a que está executando
	if(esc->executando != NULL)
		if((esc->executando)->tid == tid)
			return esc->executando;

	//Procura nas filas de apto
	for(i = 0; i < PRIORIDADES; i++){
		if(FirstFila2(esc->aptos[i]) != 0) 
			continue;			//Essa fila de prioridade está vazia
		do{
			t = (TCB_t*) GetAtIteratorFila2(esc->aptos[i]);
			if(t->tid == tid)
				return t;
		}while(!NextFila2(esc->aptos[i]));
	}

	//Procura na lista de bloqueados por cjoin
	if(FirstFila2(esc->bloq_join) == 0)
		do{
			b = (blocked*) GetAtIteratorFila2(esc->bloq_join);
			t = b->tcb;
			if(t->tid == tid)
				return t;
		}while(!NextFila2(esc->bloq_join));
	
	//Procura na fila de cada semáforo da lista de semáforosi
	if(FirstFila2(esc->semaforos) == 0)
		do{
			s = (csem_t*) GetAtIteratorFila2(esc->semaforos);
			if(FirstFila2(s->fila) == 0)
				do{	
					t = (TCB_t*) GetAtIteratorFila2(s->fila);
					if(t->tid == tid)
						return t;
				}while(!NextFila2(s->fila));			
		}while(!NextFila2(esc->semaforos));
	
	return NULL;
}

/* Liberada processos bloqueados por join pela thread tid*/
int free_blocked_by(int tid){

	blocked* b;
	int next = 0;

	//Procura na lista de bloqueados por cjoin
	if(FirstFila2(esc->bloq_join) == 0)
		do{
			b = (blocked*) GetAtIteratorFila2(esc->bloq_join);
			if(b != NULL){		
				if(b->tid == tid){
					//poe ela nos aptos
					if(put_aptos(b->tcb) != 0){
						fprintf(stderr, "Erro ao colocar processo liberado na fila de aptos.\n");
						return ERRO;
					}
					
					//se a thread estava bloqueada por esse tid tira ela da fila de bloqueados
					if(DeleteAtIteratorFila2(esc->bloq_join) != 0)
						return ERRO;
				}
				else
					next = NextFila2(esc->bloq_join);
			}
			else
				next = NextFila2(esc->bloq_join);
		}while(!next);
	return SUCESSO;	
}

void terminate_join(){

	//thread 'tid' terminou
	//faz processos de término da função anteriormente executando
	esc->executando->state = PROCST_TERMINO;

	//desalocar a stack do processo
	free(esc->executando->context.uc_stack.ss_sp);

	//libera as threads bloqueadas por tid		
	if(free_blocked_by(esc->executando->tid) != 0)
		fprintf(stderr, "Erro ao liberar processos bloqueados por %d", esc->executando->tid);

	//desalocar TCB 
	free(esc->executando);

	esc->executando = NULL;

     	dispatcher();
}


/* Funcao de debug, imprime todas thread nas filas do escalonador */
void print_escalonador(){
	TCB_t *t;
	csem_t* s;
	blocked *b;
	int i;

	if(esc->executando != NULL)
		printf("EXECUTANDO: Thread %d\n", esc->executando->tid);

	//Procura nas filas de apto
	for(i = 0; i < PRIORIDADES; i++){
		printf("APTOS %d:\n", i);
		if(FirstFila2(esc->aptos[i]) != 0) 
			continue;			//Essa fila de prioridade está vazia
		do{
			t = (TCB_t*) GetAtIteratorFila2(esc->aptos[i]);
			printf("\tThread %d\n",t->tid);
		}while(!NextFila2(esc->aptos[i]));
	}

	//Procura na lista de bloqueados por cjoin
	if(FirstFila2(esc->bloq_join) == 0){
		printf("BLOQUEADOS_JOIN:\n");
		do{
			b = (blocked*) GetAtIteratorFila2(esc->bloq_join);
			t = b->tcb;
			printf("\tThread %d\n",t->tid);
		}while(!NextFila2(esc->bloq_join));
	}

	i=0;
	//Procura na fila de cada semáforo da lista de semáforosi
	if(FirstFila2(esc->semaforos) == 0){
		printf("SEMAFOROS:\n");
		do{
			s = (csem_t*) GetAtIteratorFila2(esc->semaforos);
			if(FirstFila2(s->fila) == 0){
				printf("\tSEMAFORO %d:\n", i);
				do{	
					t = (TCB_t*) GetAtIteratorFila2(s->fila);
					printf("\t\tThread: %d\n",t->tid);
				}while(!NextFila2(s->fila));
			}
			i++;			
		}while(!NextFila2(esc->semaforos));
	}
}

/* Funcao para verificação se thread já foi bloqueada por outra */
int has_blocked_by(int tid){
	blocked* b;

	//Se a fila esta vazia ela nao tem ninguém bloqueado por ela
	if(FirstFila2(esc->bloq_join) == 0)
		do{
			b = (blocked*) GetAtIteratorFila2(esc->bloq_join);
			
			if(b->tid == tid)
				return 1;
		}while(!NextFila2(esc->bloq_join));
	
	return 0;
}

