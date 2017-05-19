#include <stdio.h>
#include <stdlib.h>
#include "../include/escalonador.h"

int main(){

	TCB_t a;

	a.ticket = 3;
	a.tid = 3;
	a.state = PROCST_EXEC;

	if(init_escalonador() != SUCESSO)
		printf("Erro na init_escalonador.\n");
	
	if(put_aptos(&a) != SUCESSO)
		printf("Erro na put_aptos.\n");

	print_escalonador();

	if(csetprio(3,1) != SUCESSO)
		printf("Erro no teste da funcao csetprio.\n");
	else if ((search_thread(3)->tid == 3))
		printf("Sucesso no teste da funcao csetprio.\n");

	print_escalonador();

	if(csetprio(3,4) == SUCESSO)
		printf("Falha no teste de limites superiores da funcao csetprio.\n");
	else 
		printf("Sucesso no teste de limites superiores da funcao csetprio.\n");


	if(csetprio(3,-1) == SUCESSO)
		printf("Falha no teste de limites inferiores da funcao csetprio.\n");
	else 
		printf("Sucesso no teste de limites inferiores da funcao csetprio.\n");

	print_escalonador();

	return 0;
}
