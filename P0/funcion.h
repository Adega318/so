#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <sys/utsname.h>


#define LNULL NULL
#define COMAND 200
#define TROCEO 10
typedef struct tNode* tPosL;
struct tNode{
    char comand[COMAND];
    tPosL next;
};
typedef tPosL tList;

//Funciones de control
int trocear(char *entrada, char* salida[]);
int procesadoC(char* Arg[], int numA,tList* L);
void printC(char* Arg[], int numA);

//Funciones de comandos
void autores(char* Arg[], int numA);
void pid(char* Arg[], int numA);
void carpeta(char* Arg[], int numA);
void fecha(char* Arg[], int numA);
void hist(char* Arg[], int numA, tList *L);
//Sub funciones del hist
void mostrarHistN(int n, tList *L);
void fullHist(tList L);
//
void comando(char* Arg[], int numA, tList *L);
void infosis(char* Arg[], int numA);
void ayuda(char* Arg[], int numA);

//Funciones de operación de la lista
void createEmptyList(tList *L);
bool isEmptyList(tList L);
tPosL first(tList L);
tPosL last(tList L);
tPosL next(tPosL P, tList L);
tPosL previous(tPosL P, tList L);
char* getData(tPosL P, tList L);
tPosL findData(int I, tList L);
bool insertData(char *I, tList *L);
void delHist( tList *L);

#endif
