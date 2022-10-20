/*
Autores:
- Enrique Adega Fernandez  e.adega@udc.es
- Antonio Buceta Paz antonio.buceta@udc.es
*/

#include "funcion.h"
#include "list.h"

int main(){
    int salida=0, numA=0, c;
	char* entrada=malloc(TMALLOC);
    char* almacenamiento[TROCEO];
    tList L;
    
    createEmptyList(&L);

    while(salida==0){
        printf("--> ");
        if(scanf("%[^\n]s", entrada)>0) insertData(entrada, &L);
        numA=trocear(entrada,almacenamiento);
        salida=procesadoC(almacenamiento,numA, &L);
		strcpy(entrada, "");
		while((c = getchar()) != '\n' && c != EOF);
    }
	free(entrada);
    delList(&L);

    return 0;
}