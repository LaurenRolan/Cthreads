#include <stdio.h>
#include <stdlib.h>
#include "../include/escalonador.h"

int main(){

	TCB_t thread;
	ucontext_t context;

	thread.tid = 0;
	thread.state = PROCST_APTO;
	thread.prio = 0;
	thread.context = context;

	if(init_escalonador() != 0)
		printf("Erro na init_escalonador\n");

	if(put_aptos(&thread) != 0)
		printf("Erro no teste de put_aptos\n");
	else
		printf("Sucesso no teste de put_aptos\n");
	
	FirstFila2(esc->aptos[0]);	

	TCB_t* t;
	t = (TCB_t*) GetAtIteratorFila2(esc->aptos[0]);

	if(t->tid == 0 && t->state == PROCST_APTO && t->prio == 0 )
		printf("Dados retornados corretamente. \n");
	
	return 0;
}
