#include <stdio.h>
#include <stdlib.h>
#include "../include/escalonador.h"
#include "../include/cthread.h"

void t1() {
	printf("2.T1 executando.\n");
	return;
}
void t2() {
	printf("3.T2 executando.\n");
	cyield();
	printf("7.Terminando T2.\n");
	return;
}
void t3() {
	printf("4.T3 executando.\n");
	return;
}
void t4() {
	printf("5.T4 executando.\n");
	cyield();
	printf("8.Terminando T4.\n");
	return;
}

int main() {
	ccreate((void* (*)(void*))t1, (void *)NULL, 0);
	ccreate((void* (*)(void*))t2, (void *)NULL, 0);
	ccreate((void* (*)(void*))t3, (void *)NULL, 0);
	ccreate((void* (*)(void*))t4, (void *)NULL, 0);
	printf("1.Começamos na main.\n");
    	cyield();
	printf("6.Voltamos à main.\n");
	cyield();
	printf("9.Acabou!\n");
	return 0;
}
