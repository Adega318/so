#ifndef COMAND_P0_H
#define COMAND_P0_H
#include "includes.h"
#include "list.h"

void autores(char* Arg[], int numA);
void pid(char* Arg[], int numA);
void carpeta(char* Arg[], int numA);
void fecha(char* Arg[], int numA);
void hist(char* Arg[], int numA, tList *L);
	void mostrarHistN(int n, tList *L);
	void fullHist(tList L);
void comando(char* Arg[], tList *L);
void infosis();
void ayuda(char* Arg[], int numA);

#endif