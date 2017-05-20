#include <stdio.h>
#include <stdlib.h>
#include "../include/escalonador.h"
#include "../include/cthread.h"

void* func(void *arg){

	printf("Sou a thread.\n");

	return NULL;
}

int main(){

	int i;	

	init_lib();

	if(ccreate(func, (void*) &i, 0) != SUCESSO)
		printf("Erro na funcao ccreate.\n");
	
	//Eu sei que nesse momento o ponteiro vai continuar na fila de aptos para lixo
	//Mas não estamos testando a dispatcher(), que é responsável por cuidar disso
	//Então tanto faz
	esc->executando = search_thread(1);

	terminate_thread();
	
	printf("Se não deu erro na free ou dispatcher, tá tudo certo!\n");

	return 0;
}
