#include <stdio.h>
#include <stdlib.h>
#include "../include/escalonador.h"
#include "../include/cdata.h"

int main(){
	if(init_lib() != SUCESSO) printf("Erro na inicializacao da biblioteca.\n");
	else {
		//Verifica se é a main que está "executando"
		if(esc->executando->tid == 0)
			printf("Sucesso no teste de inicializacao da biblioteca.\n");
	}
	return 0;
}
