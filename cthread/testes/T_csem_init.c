#include <stdio.h>
#include "../include/escalonador.h"
#include "../include/cthread.h"

int main(){
	csem_t semaforo;
	if(esc==NULL) printf("Escalonador não alocado\n");
	/*Teste sem escalonador alocado. Deve gerar erro.*/
	if(csem_init(&semaforo, 3) == SUCESSO) printf("Funcionou, mas nao deveria.\n");
	else print("Passou no teste 1.\n");

    /*Teste com o escalonador alocado. Deve funcionar.*/
	if( init_escalonador() != 0 )
		printf("Erro no teste da funcao init_escalonador\n");
    else {
        if(csem_init(&semaforo, 3) == SUCESSO) printf("Passou no teste 2.\n")
    }

    /*Teste que verifica se o semaforo esta de fato na lista do escalonador.*/
    //A fazer
}
