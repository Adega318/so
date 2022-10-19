/*
Autores:
- Enrique Adega Fernandez  e.adega@udc.es
- Antonio Buceta Paz antonio.buceta@udc.es
*/

#include "funcion.h"

int main(){
    int salida=0, numA=0;
    char  token[COMAND];
    char* almacenamiento[TROCEO];
    tList L;
    
    createEmptyList(&L);

    while(salida==0){
        printf("\n--> ");
        fgets(token,COMAND,stdin);
        insertData(token, &L);
        numA=trocear(token,almacenamiento);
        salida=procesadoC(almacenamiento,numA, &L);

    }
    delHist(&L);
    printf("exit successful\n\n");

    return 0;
}