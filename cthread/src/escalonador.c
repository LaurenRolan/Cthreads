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
	for(i = 0; i < PRIORIDADES; i++)
		esc->aptos[i] = malloc(sizeof(PFILA2));

	if(CreateFila2(esc->bloq_join) != 0)
		return ERRO_INIT;
	if(CreateFila2(esc->semaforos) != 0)
		return ERRO_INIT;
	for(i = 0; i < PRIORIDADES; i++)
		if(CreateFila2(esc->aptos[i]) != 0)
			return ERRO_INIT;

	return SUCESSO;

}

/* Poe  uma thread na fila de aptos correspondente à sua prioridade */
int put_aptos(TCB_t* newThread){ //tirei o esc

	if(newThread == NULL){
		printf("Estrutura recebida para insercao na fila de aptos tem valor %p\n", newThread);
		return ERRO_INSERCAO;
	}
	else{
		/****** Review this later, not sure if needs to do malloc of a NODE2 first, the documentatin isnt really clear about this */

		if(AppendFila2(esc->aptos[newThread->prio], (void *)newThread) != 0){
			printf("Erro na insercao de %p na fila de aptos\n", newThread);
			return ERRO_INSERCAO;
		}
	}
	
	return SUCESSO;
}
