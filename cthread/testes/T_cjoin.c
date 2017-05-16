#include <stdio.h>
#include <stdlib.h>
#include "../include/escalonador.h"

void printa(void* oi){
	printf("Reginaldo %d\n", (*(int *)oi));
}

int main(){
	int tid1, oi;
	oi = 8;
	tid1 = ccreate((void* (*)(void*))printa, (void *)&oi, 0);
	if(tid1)
		printf("Sucesso no teste de ccreate\n");
	else 
		printf("Erro\n");
	
	if(cjoin(tid1) == SUCESSO)
		return 0;

	printf("ERRO NO CJOIN\n");
	return -1;
}
