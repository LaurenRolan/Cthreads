#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cthread.h>

int main(){

	char* nomes = malloc(160);
		
	if(cidentify(nomes, -1) != 0)
		printf("Teste 1 sucesso (size negativo, erro esperado)\n %s\n", nomes); 

	nomes[0] = '\0';

	cidentify(nomes, 0);
	printf("Teste 2 (size=0)\n %s\n", nomes);

	nomes[0] = '\0';
	
	cidentify(nomes, 10);
	printf("Teste 3 (size insuficiente)\n %s\n", nomes);

	nomes[0] = '\0';

	cidentify(nomes, 150);
	printf("Teste 4 (size exacerbado)\n %s\n", nomes);

	nomes[0] = '\0';
	
	cidentify(nomes,111);
	printf("Teste 5 (size exato)\n %s\n", nomes);


	return 0;
}
