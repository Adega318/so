#include "list.h"

bool createNode(tPosL *P){
    *P=malloc(sizeof(struct tNode));
    return *P!=LNULL;
}

void createEmptyList(tList *L){
    *L=LNULL;
}

bool isEmptyList(tList L){
    return L==LNULL;
}

tPosL first(tList L){
    return L;
}

tPosL last(tList L){
    tPosL p;
    for(p=L; p->next!=LNULL; p=p->next);
    return p;
}

tPosL next(tPosL P, tList L){
    return P->next;
}

tPosL previous(tPosL P, tList L){
    tPosL p;
    if(P==L) p=LNULL;
    else for(p=L; p->next!=P; p=p->next);
    return p;
}

tPosL findData(int I, tList L){
    tPosL p=L;
    int i=1;

    if (isEmptyList(L)) p=LNULL;
    else for(i=1; i!=I; i++) p=p->next;
    return p;   
}

bool insertData(char* I,tList *L){
    tPosL q,p;
    bool aux= 1;

    if(!createNode(&q)) aux=0;
    else{
        q->comand=malloc(255);
        strcpy(q->comand, I);
        q->next=LNULL;
        if(*L==LNULL)*L=q;
        else{
            for (p = *L; p->next != LNULL; p = p->next);
            p->next = q;

        }
    }
    return aux;
}

char* getData(tPosL P, tList L){
    return P->comand;
}

void delList( tList *L){
    tPosL p,q;

    p=*L;
    while(p!=LNULL){
        q=p->next;
		free(p->comand);
        free(p);
        p=q;
    }
    *L=LNULL;
}