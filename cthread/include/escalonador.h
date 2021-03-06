/* TAD para o escalonador a ser usado na biblioteca cthreads */

#include "support.h"
#include "cdata.h"
#include "cthread.h"

#define ERRO -1
#define SUCESSO 0
#define PRIORIDADES 4

typedef struct s_escalonador{

	PFILA2 bloq_join;		//lista das threads bloqueadas por cjoin
	PFILA2 semaforos;		//lista de semaforos do usuário
	PFILA2 aptos[PRIORIDADES]; 	//quatro filas de prioridade das threads aptas
	TCB_t* executando;		//TCB do processo executando no momento
	int tidCounter;			//gerador de IDs de threads
	ucontext_t terminate; 		//contexto para a função de encerramento de threads

}escalonador;

typedef struct s_blocked{
	
	TCB_t* tcb;			//TCB do processo bloqueado
	int tid;			//tid do processo pelo qual ele está esperando

}blocked;

extern escalonador* esc;

/* Inicializa a estrutura necessaria ao escalonador */
int init_escalonador();

/* Poe  uma thread na fila de aptos correspondente à sua prioridade */
int put_aptos(TCB_t *newThread);

/* Dispatcher é responsável por escolher qual a próxima thread que irá executar */
int dispatcher();

/* Quando a primeira chamada é efetuada, a biblioteca é inicializada*/
int init_lib();

/* Encerração de thread e desalocação de estruturas relacioandas a ela*/
void terminate_thread();

/* Procura por uma thread a partir de um tid */
TCB_t* search_thread(int tid);

/* Retira da lista de bloqueados as thread bloqueados por 'tid' e bota-as na fila de aptos */
int free_blocked_by(int tid);

/* Encerracao da thread em cjoin e desalocacao de estruturas */
void terminate_join();

/* Imprime todas filas */
void print_escalonador();

/* Retorna se uma thread já está sendo bloqueada por um tid*/
int has_blocked_by(int tid);
