#include <stdio.h>
#include <stdlib.h>
#include "../include/escalonador.h"


int main(){

	TCB_t *t, thr[10];
	blocked b;
	int i;
	csem_t sem[2];

	if(init_escalonador() != 0)
		printf("Erro na inicializacao do escalonador.\n");
	
	if(search_thread(0) == NULL)
		printf("Sucesso no teste com filas vazias.\n");


	//Preenche filas de prioridades
	for(i = 0; i < PRIORIDADES; i++){
		thr[i].tid = i;
		thr[i].ticket = i;
		put_aptos(&thr[i]);
	}
	
	//Mais de um na mesma fila	
	thr[4].tid = 4;
	thr[4].ticket = 3;
	put_aptos(&thr[4]);

	//Executando
	thr[5].tid = 5;
	thr[5].ticket = 0;
	thr[5].state = PROCST_EXEC;
	esc->executando = &thr[5];
	
	//Bloqueado cjoin
	thr[6].tid = 6;
	thr[6].ticket = 0;
	thr[6].state = PROCST_BLOQ;
	b.tcb = &thr[6];
	b.tid = 3;
	AppendFila2(esc->bloq_join, (void*)&b);
	
	//Bloqueado semaforo
	thr[7].tid = 7;
	thr[7].ticket = 0;
	thr[8].tid = 8;
	thr[8].ticket = 0;
	thr[9].tid = 9;
	thr[9].ticket = 0;
	thr[7].state = thr[8].state = thr[9].state = PROCST_BLOQ;
	if(csem_init(&sem[0],0) != SUCESSO || csem_init(&sem[1],0) != SUCESSO)
		printf("Falha na inicializacao do semaforo.\n");
	AppendFila2(sem[0].fila, (void *) &thr[7]);
	AppendFila2(sem[0].fila, (void *) &thr[8]);
	AppendFila2(sem[1].fila, (void *) &thr[9]);

	t = search_thread(5);
	if(t->tid == 5 && t->state == PROCST_EXEC && t->ticket == 0)
		printf("Sucesso no teste de procura no executando.\n");
	else 
		printf("Falha no teste de procura no executando.\n");

	for(i = 0; i <= PRIORIDADES; i++){
		t = search_thread(i);
		if(t->tid == i && t->state == PROCST_APTO && (t->ticket == i || (t->ticket == 3 && i == 4)))
			printf("Sucesso no teste de procura no apto %d.\n", i);
		else
			printf("Falha no teste de procura no apto %d.\n", i);
	}

	t = search_thread(6);
	if(t->tid == 6 && t->state == PROCST_BLOQ && t->ticket == 0)
		printf("Sucesso no teste de procura no cjoin.\n");
	else 
		printf("Falha no teste de procura no cjoin.\n");

	for(i = 7; i < 10; i++){
		t = search_thread(i);
		if(t->tid == i && t->state == PROCST_BLOQ && t->ticket == 0)
			printf("Sucesso no teste de procura no semaforo %d.\n", i-6);
		else
			printf("Falha no teste de procura no semaforo %d.\n", i-6);

	}

	return 0;
}
