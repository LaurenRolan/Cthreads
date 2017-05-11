#include <stdio.h>
#include "../include/escalonador.h"
#include "../include/cthread.h"

int main(){
	csem_t semaforo;


    /*Teste com o escalonador alocado. Deve funcionar.*/
	if( init_escalonador() != 0 )
		printf("Erro no teste da funcao init_escalonador\n");
    else {
        if(csem_init(&semaforo, 3) == SUCESSO) {
		printf("Passou no teste.\n");
		printf("Alocou %d recursos.\n", semaforo.count); // dá erro
    }

    /*Teste que verifica se o semaforo esta de fato na lista do escalonador.*/
    //A fazer
}
