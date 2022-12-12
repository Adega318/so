/*
Autores:
- Enrique Adega Fernandez  e.adega@udc.es
- Antonio Buceta Paz antonio.buceta@udc.es
*/

#include "funcion.h"
#include "list.h"
#include "comandP2.h"


int main(){
	int salida=0, numA=0, c, error=0;
	char* entrada=malloc(TMALLOC);
	char* almacenamiento[TROCEO];
	tList L;
	tListM LM;
	jobList jobL;
	tPosLM p;
	tNodeMem d;
	
	createEmptyList(&L);
	createEmptyListM(&LM);
	createJobList(&jobL);

	while(salida==0){
		printf("--> ");
		if(scanf("%[^\n]s", entrada)>0) insertData(entrada, &L);
		numA=trocear(entrada,almacenamiento);
		salida=procesadoC(almacenamiento,numA, &L, &LM, &jobL);
		strcpy(entrada, "");
		while((c = getchar()) != '\n' && c != EOF);
	}

	free(entrada);
	delList(&L);
	p=LM;
	while(p!=NULL){
		d=getDataM(p, LM);
		p=nextM(p, LM);
		deallocateAddr(NULL, -1, &LM, d.hex);
	}
	emptyJobList(&jobL);

	return 0;
}