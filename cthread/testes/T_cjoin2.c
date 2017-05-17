#include <stdio.h>
#include <stdlib.h>
#include "../include/escalonador.h"

/**** Teste com duas threads esperando a mesma thread acabar **/


void printa(void* oi){
	printf("Executando thread1 %d\n", (*(int *)oi));

}

void socorro(void *tid){
	printf("Esperando thread%d...\n", (*(int *)tid));
	cjoin((*(int *)tid));
	printf("Executando thread2 \n");
}

int main(){
	int tid1, tid2, oi;
	oi = 8;

	if((tid1 = ccreate((void* (*)(void*))printa, (void *)&oi, 1)))
		printf("Sucesso TID1\n");
	else printf("Erro TID1");
	if((tid2 = ccreate((void* (*)(void*))socorro, (void *)&tid1, 0)))
		printf("Sucesso TID2\n");
	else printf("Erro TID2");


	if(cjoin(tid1) == SUCESSO){
		printf("Sucesso no teste da cjoin.\n");
	}
	else 
		printf("Erro no teste da cjoin.\n");

	if(cjoin(tid2) == SUCESSO){
		printf("Sucesso no segundo teste da cjoin.\n");
	}
	else
		printf("Erro no segundo teste da cjoin.\n");

	return 0;
}
