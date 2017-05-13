#include <stdio.h>
#include <stdlib.h>
#include "../include/escalonador.h"


int main(){

	TCB_t* t;

	if(init_escalonador() != 0)
		printf("Erro na inicializacao do escalonador.\n");
	
	if(search_thread(0) == NULL)
		printf("Sucesso no teste com filas vazias.\n");

	/*Adicionar:
		1. Teste para achar na executando
		2. Teste para achar na aptos0,1,2,3
		3. Teste para achar na bloqueados join
		4. Teste para achar em um semaforo
	*/


	return 0;
}
