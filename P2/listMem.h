#ifndef LIST_H
#define LIST_H

#include "includes.h"

#define LNULL NULL

typedef struct tNode* tPosL;
struct tNode{
    char* hex;
    int space;
    time_t creationTime;
    char* tipoMem;
    int key;
    tPosL next;
};
typedef tNode tNode;
typedef tPosL tList;

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