#ifndef LISTM_H
#define LISTM_H

#include "includes.h"

#define LNULL NULL

typedef struct tNodeMem* tPosLM;
typedef struct tNodeMem{
	void* hex;
	size_t space;
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
tPosLM findHex(void* hex, tListM L);
tPosLM findSizeInType(int S, char* type, tListM LM);
tPosLM finkey(key_t clave, tListM LM);
bool insertDataM(tNodeMem I, tListM *L);
void delListM( tListM *L);
void delPos(tPosLM p, tListM* LM);
void printType(char* type, tListM L);

#endif