/** Programa de teste unitário da funcao init_escalonador() **/

#include <stdio.h>
#include "../include/escalonador.h"

int main(){
	
	if( init_escalonador() != 0 )
		printf("Erro no teste da funcao init_escalonador\n");
	else
		printf("Sucesso no teste da funcao init_escalonador\n");

	return 0;		
}
