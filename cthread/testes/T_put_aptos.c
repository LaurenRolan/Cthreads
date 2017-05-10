#include <stdio.h>
#include <stdlib.h>
#include "../include/escalonador.h"

int main(){

	TCB_t thread[5], *t;
	ucontext_t context;
	int i;

	//Teste para inserção em cada fila
	for(i = 0; i < PRIORIDADES; i++){
		thread[i].tid = i;
		thread[i].state = PROCST_EXEC;
		thread[i].ticket = i;
		thread[i].context = context;

		if(init_escalonador() != 0)
			printf("Erro na init_escalonador\n");

		if(put_aptos(&thread[i]) != 0)
			printf("Erro no teste de put_aptos\n");
		else
			printf("Sucesso no teste de put_aptos\n");
	
		FirstFila2(esc->aptos[i]);	

		t = (TCB_t*) GetAtIteratorFila2(esc->aptos[i]);

		if(t->tid == i && t->state == PROCST_APTO && t->ticket == i )
			printf("Dados retornados corretamente. \n");
	}	

	//teste de segunda insercao na mesma fila
	thread[i].tid = i+1;
	thread[i].ticket = i-1;
	thread[i].state = PROCST_EXEC;
	thread[i].context = context;

	if(put_aptos(&thread[i]) != 0)
		printf("Erro no teste da segunda insercao na fila de aptos.\n");
	else
		printf("Sucesso no teste da segunda insercao.\n");

	NextFila2(esc->aptos[i-1]);
	t = (TCB_t*) GetAtIteratorFila2(esc->aptos[i-1]);
		
	if(t->tid == i+1 && t->state == PROCST_APTO && t->ticket == i-1 )
		printf("Dados retornados corretamente do segundo teste. \n");

	return 0;
}
