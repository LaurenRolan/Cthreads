/** Programa de teste unitário da funcao init_escalonador() **/

#include <stdio.h>
#include "../include/escalonador.h"

int main(){
	escalonador esc;	

	if( init_escalonador(&esc) != 0 )
		printf("Erro no teste da funcao init_escalonador\n");

	return 0;		
}
