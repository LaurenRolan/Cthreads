#include <stdio.h>
#include <stdlib.h>
#include "../include/cthread.h"

void func(void* a){

	printf("Sigh no more, ladies, sigh no more,\nMen were deceivers ever,-\nOne foot in sea and one on shore,\nTo one thing constant never.\n");
	printf("Except by, of course, this fine little argument here: %d\n", *((int *)a));

	return;
}

int main(){

	int i = 2;

	if(ccreate((void* (*)(void*))func,(void *)&i,0) != 0)
		printf("Erro no teste.\n");
	else
		printf("Sucesso no teste de ccreate.\n");
	 
	return 0;
}
