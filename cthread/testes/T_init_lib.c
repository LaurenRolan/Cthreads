#include <stdio.h>
#include <stdlib.h>
#include "../include/escalonador.h"
#include "../include/cdata.h"

int main(){
	if(init_lib() != SUCESSO) printf("Erro na inicializacao da biblioteca.\n");
	else {
		//Verifica se é a main que está "executando"
		printf("O tid da thread executando e %d\n", esc->executando->tid);
	}
	return 0;
}
