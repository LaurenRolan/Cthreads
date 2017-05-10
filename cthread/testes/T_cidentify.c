#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/cthread.h"

int main(){

	char* nomes = malloc(160);
	
	cidentify(nomes, 0);
	printf("Teste 1 (size=0)\n %s\n", nomes);

	cidentify(nomes, 10);
	printf("Teste 2 (size insuficiente)\n %s\n", nomes);

	cidentify(nomes, 150);
	printf("Teste 3 (size exacerbado)\n %s\n", nomes);

	cidentify(nomes,111);
	printf("Teste 4 (size exato)\n %s\n", nomes);


	return 0;
}
