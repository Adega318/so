#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <dirent.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/stat.h>



#define LNULL NULL
#define TROCEO 50
#define TMALLOC 4090

typedef struct tNode* tPosL;
struct tNode{
    char* comand;
    tPosL next;
};
typedef tPosL tList;

//Funciones de control
int trocear(char *entrada, char* salida[]);
int procesadoC(char* Arg[], int numA,tList* L);
void printC(char* Arg[], int numA);

//Funciones de comandos
//p0
void autores(char* Arg[], int numA);
void pid(char* Arg[], int numA);
void carpeta(char* Arg[], int numA);
void fecha(char* Arg[], int numA);
void hist(char* Arg[], int numA, tList *L);
	void mostrarHistN(int n, tList *L);
	void fullHist(tList L);
void comando(char* Arg[], int numA, tList *L);
void infosis(char* Arg[], int numA);
void ayuda(char* Arg[], int numA);
//p1
void create(char* Arg[], int numA);
void statfun(char* Arg[], int numA);
	void statprint (bool lon, bool link, bool acc, char* pArg, char* Arg, struct stat stats);
	char LetraTF (mode_t m);
	char * ConvierteModo (mode_t m);
void list();
	void listrec(char* Arg, bool reca, bool recb, bool hid, bool lon, bool link, bool acc);
void delete();
void deltree();


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
void delList( tList *L);

#endif