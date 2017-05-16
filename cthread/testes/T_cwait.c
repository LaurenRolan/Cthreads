#include <stdio.h>
#include <stdlib.h>
#include "../include/escalonador.h"
#include "../include/cthread.h"

csem_t semaforo;

void thread(void *arg) {
    printf("Ha %d recursos.\n", semaforo.count); //3
    cwait(&semaforo);
    printf("Ha %d recursos.\n", semaforo.count); //2
    cwait(&semaforo);
    printf("Ha %d recursos.\n", semaforo.count); //1
    cwait(&semaforo);
    printf("Ha %d recursos.\n", semaforo.count); //0
    cwait(&semaforo);
    return;
}

int main() {

    if(ccreate((void* (*)(void*))thread,(void *)NULL, 0) != 0)
		printf("Erro no teste.\n");
	else {
        csem_init(&semaforo, 3);
        cjoin(1);
        csignal(&semaforo); //será que funciona?
	}
	return 0;
}
