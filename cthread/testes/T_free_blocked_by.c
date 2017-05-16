#include <stdio.h>
#include <stdlib.h>
#include "../include/escalonador.h"

int main(){

	blocked b[3];
	TCB_t t[3], *t1;	
	int i;
	
	if(init_lib() != 0)
		printf("Erro na funcao init_lib.\n");
	else
		printf("Sucesso na funcao init_lib.\n");

	t[0].state = PROCST_BLOQ;
	t[0].ticket = 0;
	t[0].tid = 0;
	b[0].tcb = &t[0];
	b[0].tid = 1;

	t[1].state = PROCST_BLOQ;
	t[1].ticket = 0;
	t[1].tid = 1;
	b[1].tcb = &t[1];
	b[2].tid = 2;

	t[2].state = PROCST_BLOQ;
	t[2].ticket = 0;
	t[2].tid = 2;
	b[2].tcb = &t[2];
	b[2].tid = 1;

	for(i = 0; i < 3; i++){
		AppendFila2(esc->bloq_join, (void *)&b[i]);
	}

	if(free_blocked_by(1) != 0)
		printf("Erro no retorno da funcao free_blocked_by.\n");
	else
		printf("Sucesso no retorno da funcao free_blocked_by.\n");
	
	if(FirstFila2(esc->aptos[0]) == 0)
		do{
			t1 = (TCB_t*) GetAtIteratorFila2(esc->aptos[0]);
			printf("Thread liberada: %d\n", t1->tid);
		}while(!NextFila2(esc->aptos[0]));
	else 
		printf("Erro no teste: funcoes nao foram adicionadas na fila de aptos.\n");
	
	printf("Se as threads 0 e 2 foram liberadas, esta correto.\n");

	return SUCESSO;
}
