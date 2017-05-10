#include "escalonador.h"
#include "cthread.h"
#include <stdio.h>
#include <stdlib.h>

escalonador* esc;

int csem_init(csem_t *sem, int count){
    sem = malloc(sizeof(csem_t));
	sem->count = count;
	if(esc == NULL || AppendFila2(esc->semaforos, &sem)!=0){ //oremos para que não dê erríneos
        return ERRO_INIT;
	}
	return SUCESSO;
}

int cwait(csem_t *sem){
    return 0;
}
int csignal(csem_t *sem){
    return 0;
}
