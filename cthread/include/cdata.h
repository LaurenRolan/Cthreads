/*
 * cdata.h: arquivo de inclusão de uso apenas na geração da libpithread
 *
 * Esse arquivo pode ser modificado. ENTRETANTO, deve ser utilizada a TCB fornecida
 *
 * Versão de 25/04/2017
 *
 */
#include "support.h"
#include <ucontext.h>

#ifndef __cdata__
#define __cdata__

#define	PROCST_CRIACAO	0
#define	PROCST_APTO	1
#define	PROCST_EXEC	2
#define	PROCST_BLOQ	3
#define	PROCST_TERMINO	4

/* NÃO ALTERAR ESSA struct */
typedef struct s_TCB { 
	int		tid; 		// identificador da thread
	int		state;		// estado em que a thread se encontra
					// 0: Criação; 1: Apto; 2: Execução; 3: Bloqueado e 4: Término
	int 		prio;		// "bilhete" de loteria da thread, para uso do escalonador
	ucontext_t 	context;	// contexto de execução da thread (SP, PC, GPRs e recursos) 
} TCB_t; 

#endif

/* Estrutura para controle de semáforo */
typedef struct s_sem{
	int count; 			//indica se recurso está ocupado ou não (livre > 0, ocupado <= 0)
	PFILA2 fila; 			//ponteiro para uma fila de threads bloqueadas no semáforo
}csem_t;
