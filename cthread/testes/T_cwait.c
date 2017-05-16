#include <stdio.h>
#include <stdlib.h>
#include "../include/escalonador.h"
#include "../include/cthread.h"


csem_t semaforo;

void thread(void *a) {
    	printf("1.Ha %d recursos.\n", semaforo.count); //3
    	cwait(&semaforo);
    	printf("2.Ha %d recursos.\n", semaforo.count); //2
    	cwait(&semaforo);
    	printf("3.Ha %d recursos.\n", semaforo.count); //1
    	cwait(&semaforo);
    	printf("4.Ha %d recursos.\n", semaforo.count); //0
    	cwait(&semaforo);
	printf("7.Thread voltou a executar.\n");
	printf("8.Ha %d recursos.\n", semaforo.count);
    return;
}

int main() {
	int i = 2;

    if(ccreate((void* (*)(void*))thread, (void *)&i,0) != 1)
		printf("0.Erro no teste.\n");
	else {
        csem_init(&semaforo, 3);
        cyield();
	printf("5.Voltamos à main, uma vez que não há recursos.\n");
        csignal(&semaforo);
	printf("6.Main liberou recurso.\n");
	cyield();
	}
	printf("9.Terminamos!");
	return 0;
}
