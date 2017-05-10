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

	if(init_escalonador(esc) != 0)
		printf("Erro na init_escalonador\n");

	if(put_aptos(&thread) != 0)
		printf("Erro no teste de put_aptos\n");
	else
		printf("Sucesso no teste de put_aptos\n");
	
	return 0;
}
