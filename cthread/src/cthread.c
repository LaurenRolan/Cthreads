#include "escalonador.h"
#include "cthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

escalonador* esc;

int ccreate (void* (*start)(void*), void *arg, int prio){

	//biblioteca ainda não inicializada
	if(esc == NULL)
		init_lib();

	TCB_t* t;
	ucontext_t c;
	char stack[SIGSTKSZ];	

	t = malloc(sizeof(TCB_t));
	t->ticket = prio;
	esc->tid = esc->tid + 1;
	t->tid = esc->tid;
	t->state = PROCST_CRIACAO;

	getcontext(&c);
	c.uc_stack.ss_sp = stack;
	c.uc_stack.ss_size = sizeof(stack);

	makecontext(&c, (void (*)(void))start, 1, arg);
	t->context = c;
	
	if(put_aptos(t) != 0)
		return ERRO;
	
	return SUCESSO;

}

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
