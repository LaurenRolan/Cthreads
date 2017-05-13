#include <stdio.h>
#include <stdlib.h>
#include "../include/escalonador.h"
#include "../include/cthread.h"

int main() {
	csem_t semaforoReal, semaforoFake;
	TCB_t *fake1, *fake2, *fake3;
	TCB_t *primApta;

	fake1 = malloc(sizeof(TCB_t));
	fake1->tid = 1;
	fake1->ticket = 0;

	fake2 = malloc(sizeof(TCB_t));
	fake2->tid = 2;
	fake2->ticket = 0;

	fake3 = malloc(sizeof(TCB_t));
	fake3->tid = 3;
	fake3->ticket = 0;

	init_lib();
	csem_init(&semaforoReal, 0);

	printf("SemaforoReal inicializado com %d recursos.\n", semaforoReal.count);
	
	//Põe falsas threads na fila do semáforo
	AppendFila2(semaforoReal.fila, (void*) fake1);
	AppendFila2(semaforoReal.fila, (void*) fake2);
	AppendFila2(semaforoReal.fila, (void*) fake3);

	//Libera cada uma dessas falsas threads
	csignal(&semaforoReal);
	printf("SemaforoReal agora tem %d recursos disponíveis.\n", semaforoReal.count);
	
	csignal(&semaforoReal);
	printf("SemaforoReal agora tem %d recursos disponíveis.\n", semaforoReal.count);

	csignal(&semaforoReal);
	printf("SemaforoReal agora tem %d recursos disponíveis.\n", semaforoReal.count);

	//Testa se é possível dar csignal em um semáforo não alocado
	if(csignal(&semaforoFake)==SUCESSO) printf("Erro na funcao csignal.\n"); //Não deve ser impresso.

	FirstFila2(esc->aptos[0]);
	primApta = (TCB_t *) GetAtIteratorFila2(esc->aptos[0]);
	
	//Verifica se csignal + putAptos funciona
	if(semaforoReal.count == 3 && primApta->tid == 1) printf("Teste realizado com sucesso.\n");

	free(fake1);
	free(fake2);
	free(fake3);
	
	return 0;
}
