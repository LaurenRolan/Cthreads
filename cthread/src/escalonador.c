#include <stdio.h>
#include <stdlib.h>
#include "escalonador.h"

escalonador* esc;

/* Inicializa a estrutura necessaria ao escalonador */
int init_escalonador(){
	int i;

	esc = malloc(sizeof(escalonador));	
	esc->bloq_join = malloc(sizeof(PFILA2));
	esc->semaforos = malloc(sizeof(PFILA2));
	esc->executando = malloc(sizeof(TCB_t));
	
	for(i = 0; i < PRIORIDADES; i++)
		esc->aptos[i] = malloc(sizeof(PFILA2));

	if(CreateFila2(esc->bloq_join) != 0)
		return ERRO;
	if(CreateFila2(esc->semaforos) != 0)
		return ERRO;
	for(i = 0; i < PRIORIDADES; i++)
		if(CreateFila2(esc->aptos[i]) != 0)
			return ERRO;

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
	
	int i;
	TCB_t* temp;

	for(i=0; i < PRIORIDADES; i++){
		if(FirstFila2(esc->aptos[i]) != 0 && LastFila2(esc->aptos[i]) != 0)	//Verifica se a fila é vazia
			continue;
		if(( temp = (TCB_t*) GetAtIteratorFila2(esc->aptos[i]) ) && temp != NULL){
			temp->state = PROCST_EXEC;
			esc->executando = temp;
			if(setcontext(&(temp->context)) == -1){
				fprintf(stderr, "Erro ao mudar de contexto no dispatcher. Thread ID %d \n", temp->tid);
				return ERRO;
			}
			break;
		}
	}
	
	return ERRO; //não existe nenhuma thread apta no momento
}
