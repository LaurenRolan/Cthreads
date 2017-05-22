#include <stdio.h>
#include <cthread.h>
#include "../include/escalonador.h"

void* func1(void * a){

	printf("1.8.\tEle era, como todos gatos,\n");
	csetprio(esc->executando->tid,3);
	cyield();
	printf("11.13.\tNo entanto, havia um rato,\n");
	return NULL;
}

void* func2(void *a){

	printf("3.\tNo entanto, havia um rato,\n");
	printf("4.\tAh, havia sim um rato.\n");
	return NULL;
}

void* func3(void *a){

	printf("5.\tPara ele nada havia de mais nesses gatos\n");
	cyield();
	printf("6.\tBem, diga isso para eles, senhor Rato.\n");
	printf("7.\tQue sim, havia um gato,\n");
	return NULL;
}

void* func4( void*a){

	printf("9.\tMandao, idiota e presunçoso, esse gato!\n");
	printf("10.\tE para isso o gato falava:\n");
	csetprio(4,1);
	cyield();
	printf("15.\tMal sabiam eles que na verdade todos eram\n");
	return NULL;
}

void* func5(void *a){

	printf("12.\tQue nao sabia nada sobre gatos:\n");
	cyield();	
	printf("16.\tGatos e ratos\n");
	return NULL;
}

int main(){

	int i;

	printf("Esse teste baseia-se na correta ordem do poema para averiguacao de corretude.\n");

	ccreate(func1, &i, 0);
	ccreate(func2, &i, 1);
	ccreate(func3, &i, 1);	
	ccreate(func1, &i, 2);
	ccreate(func4, &i, 3);
	ccreate(func5, &i, 3);

	printf("0.\tEra uma vez um gato\n");
	cyield();
	printf("2.\tMuito orgulhoso, muito certo, era um fato.\n");
	csetprio(0, 3);

	cyield();
	printf("14.\tQue devia mesmo era voltar a ser um rato.\n");
	cyield();
	printf("17.\tE seres vivos também.\n");
	
	return 0;
}
