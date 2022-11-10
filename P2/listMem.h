#ifndef LISTM_H
#define LISTM_H

#include "includes.h"

#define LNULL NULL

typedef struct tNodeMem* tPosLM;
typedef struct tNodeMem{
	void* hex;
	int space;
	time_t creationTime;
	char* tipoMem;
	int key;
	tPosLM next;
} tNodeMem;
typedef tPosLM tListM;

void createEmptyListM(tListM *L);
bool isEmptyListM(tListM L);
tPosLM firstM(tListM L);
tPosLM lastM(tListM L);
tPosLM nextM(tPosLM P, tListM L);
tPosLM previousM(tPosLM P, tListM L);
tNodeMem getDataM(tPosLM P, tListM L);
tPosLM findDataM(int I, tListM L);
bool insertDataM(tNodeMem I, tListM *L);
void delListM( tListM *L);
void printType(char* type, tListM* L);

#endif