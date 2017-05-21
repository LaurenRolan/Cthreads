#include <stdio.h>
#include <stdlib.h>
#include "../include/escalonador.h"

#define N 	500  //NÚMERO DE THREADS CRIADAS

void printa(void* oi){
	printf("Executando thread1 %d\n", (*(int *)oi));
}

void socorro(void *tid){
	printf("Executando thread%d\n", (*(int *)tid +1));
}

int main(){
	int tid[N], oi, i;
	oi = 8;
	printf("%d \n", cjoin(0));
	if((tid[0] = ccreate((void* (*)(void*))printa, (void *)&oi, 1)))
		printf("Sucesso TID1\n");
	else printf("Erro TID1");

	for(i = 1; i <= N-1; i++){
		if((tid[i] = ccreate((void* (*)(void*))socorro, (void *)&tid[i-1], 0)))
			printf("Sucesso TID%d\n", i+1);
		else printf("Erro TID%d\n", i+1);
	}

	if(cjoin(tid[0]) == SUCESSO){
		printf("Sucesso no teste da cjoin.\n");
		return 0;
	}

	printf("ERRO NO CJOIN\n");
	return -1;
}
