#include <stdio.h>
#include "../include/escalonador.h"
#include "../include/cthread.h"

int main(){
	csem_t semaforo;
	csem_t* sem;

    /*Teste com o escalonador alocado. Deve funcionar.*/
	if( init_escalonador() != 0 )
		printf("Erro no teste da funcao init_escalonador\n");
    	else {
        	if(csem_init(&semaforo, 3) == SUCESSO) {
			printf("Passou no teste.\n");
			printf("Alocou %d recursos.\n", semaforo.count);
		}
    	}

    /*Teste que verifica se o semaforo esta de fato na lista do escalonador.*/
	FirstFila2(esc->semaforos);
	sem = (csem_t*) GetAtIteratorFila2(esc->semaforos);
	
	if(sem->count == 3)	
		printf("Inseriu na lista do escalonador corretamente.\n");
	else
		printf("Falhou no teste de insercao na lista do escalonador.\n");	
	
	return 0;
}
