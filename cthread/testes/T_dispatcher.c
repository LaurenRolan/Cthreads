#include <stdio.h>
#include <stdlib.h>
#include "../include/escalonador.h"

void funcTest(void *arg){

	printf("He that hath a beard is more than a youth, and he that hath no beard is less than a man: and he that is more than a youth is not for me, and he that is less than a man, I am not for him.\n");
	printf("Oh, and this is my %d-nth time saying this to this guy. -Beatrice\n",*((int *)arg));
	return;
}

int main(){

	TCB_t t;
	ucontext_t main_context, c;
	int i = 2;

	init_escalonador();

	t.tid = 0;
	t.ticket = 0;
	t.state = PROCST_APTO;	

	char stack[SIGSTKSZ];
	getcontext(&c);
	c.uc_link          = &main_context;
	c.uc_stack.ss_sp   = stack;
	c.uc_stack.ss_size = sizeof(stack);

	makecontext(&c, (void (*)(void))funcTest, 1, (void *)&i);
	t.context = c;

	if(put_aptos(&t) == ERRO)
		printf("Erro na funcao put_aptos.\n");
	int control = 0;
	getcontext(&main_context);
	if(control == 0){
		control = 1;
		if(dispatcher() == ERRO)
			printf("Erro na funcao dispatcher.\n");
		else
			printf("Voltou da dispatcher? Nope. Isso na real nunca eh para executar.\n");
	}
	
	printf("Teste realizado com sucesso\n");

	return 0;
}
