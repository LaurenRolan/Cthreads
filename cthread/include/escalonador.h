/* TAD para o escalonador a ser usado na biblioteca cthreads */

#include "support.h"
#include "cdata.h"

#define ERRO_INSERCAO -1
#define ERRO_INIT -1
#define SUCESSO 0
#define PRIORIDADES 4

typedef struct s_escalonador{

	PFILA2 bloq_join;
	PFILA2 semaforos;
	PFILA2 aptos[PRIORIDADES]; 

}escalonador;

/* Inicializa a estrutura necessaria ao escalonador */
int init_escalonador(escalonador* esc){
	int i;

	if(CreateFila2(bloq_join) != 0)
		return ERRO_INIT;
	if(CreateFila2(semaforos != 0)
		return ERRO_INIT;
	for(i = 0; i < PRIORIDADES; i++)
		if(CreateFila2(aptos[i]) != 0)
			return ERRO_INIT;

	return SUCESSO;

}

/* Poe  uma thread na fila de aptos correspondente à sua prioridade */
int put_aptos(TCB_t newThread){

	if(newThread == NULL){
		printf("Estrutura recebida para insercao na fila de aptos tem valor %p\n", newThread);
		return ERRO_INSERCAO;
	}
	else{
		if(AppendFila2(aptos[newThread->prio], &newThread) != 0){
			printf("Erro na insercao de %p na fila de aptos\n", newThread);
			return ERRO_INSERCAO;
		}
	}
	
	return SUCESSO;
}
