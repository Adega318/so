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
#define TROCEO 50 //numero maximo de argumentos de entrada
#define TMALLOC 4090 //tamaño maximo de entrada

struct modCom{
	bool reca;
	bool recb;
	bool hid;
	bool lon;
	bool link;
	bool acc;
};

typedef struct tNode* tPosL;
struct tNode{
    char* comand;
    tPosL next;
};
typedef tPosL tList;

//Funciones de control
int trocear(char *entrada, char* salida[]);
int procesadoC(char* Arg[], int numA,tList* L);

//Funciones de comandos
//p0
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
//p1
struct modCom ModComCreate();
struct modCom ModComSet(struct modCom modArg);
void create(char* Arg[], int numA);
void statfun(char* Arg[], int numA);
	void statprint (struct modCom modArg, char* pArg, char* Arg, struct stat stats);
	char LetraTF (mode_t m);
	char * ConvierteModo (mode_t m);
void list();
	void listrec(char* Arg, struct modCom modArg);
void delete(char *Arg[], int numA);
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