#include "escalonador.h"
#include "cthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

escalonador* esc;

int csem_init(csem_t *sem, int count){
    
	//biblioteca ainda não inicializada	
	if(esc == NULL)
		init_lib();	

	sem = malloc(sizeof(csem_t));
	sem->count = count;
	if(esc == NULL || AppendFila2(esc->semaforos, &sem)!=0){ //oremos para que não dê erríneos
        	return ERRO;
	}
	return SUCESSO;
}

int cwait(csem_t *sem){
    return 0;
}
int csignal(csem_t *sem){
    return 0;
}

int cidentify (char *name, int size){

	char *str = "\tLauren Silva Rolan Sampaio - ........\n\tLeonardo da Luz Dorneles - 00262516\n\tNatalia Gubiani Rampon - 00262512\n";

	//biblioteca ainda não inicializada
	if(esc == NULL)
		init_lib();

	if(size < 0)
		return ERRO;


	memcpy(name, str, size);

	if(size == 0)
		name[0] = '\0';
	else
		name[size-1] = '\0';

	return SUCESSO;
}
