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
	TCB_t* executando;

}escalonador;

extern escalonador* esc;

/* Inicializa a estrutura necessaria ao escalonador */
int init_escalonador();

/* Poe  uma thread na fila de aptos correspondente à sua prioridade */
int put_aptos(TCB_t *newThread);


