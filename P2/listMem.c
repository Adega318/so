#include "listMem.h"

bool createNodeM(tPosLM *P){
    *P=malloc(sizeof(struct tNodeMem));
    return *P!=LNULL;
}

void createEmptyListM(tListM *L){
    *L=LNULL;
}

bool isEmptyListM(tListM L){
    return L==LNULL;
}

tPosLM firstM(tListM L){
    return L;
}

tPosLM lastM(tListM L){
    tPosLM p;
    for(p=L; p->next!=LNULL; p=p->next);
    return p;
}

tPosLM nextM(tPosLM P, tListM L){
    return P->next;
}

tPosLM previousM(tPosLM P, tListM L){
    tPosLM p;
    if(P==L) p=LNULL;
    else for(p=L; p->next!=P; p=p->next);
    return p;
}

tPosLM findDataM(int I, tListM L){
    tPosLM p=L;
    int i=1;

    if (isEmptyListM(L)) p=LNULL;
    else for(i=1; i!=I; i++) p=p->next;
    return p;   
}

bool insertDataM(tNodeMem Data,tListM *L){
    tPosLM q,p;
    bool aux= 1;

    if(!createNodeM(&q)) aux=0;
    else{
        *q=Data;
        q->next=LNULL;
        if(*L==LNULL) *L=q;
        else{
            for (p = *L; p->next != LNULL; p = p->next);
            p->next = q;

        }
    }
    return aux;
}

tNodeMem getDataM(tPosLM P, tListM L){
    return *P;
}

void delListM( tListM *L){
    tPosLM p,q;

    p=*L;
    while(p!=LNULL){
        q=p->next;
        free(p);
        p=q;
    }
    *L=LNULL;
}

void printType(char* type, tListM* L){
    tPosLM p=*L;
    tNodeMem data;
    struct tm *time;
    char fecha[100];
    

    if(!isEmptyListM(*L))while(p!=LNULL){
        data=getDataM(p, *L);
        if(type==NULL || strcmp(data.tipoMem, type)==0){
            time= localtime(&data.creationTime);
            strftime(fecha, 100,"%b %d %H:%M ", time);
            printf("      %p              %d %s %s", 
            data.hex, data.space, fecha, data.tipoMem);
            if(strcmp(data.tipoMem, "malloc")!=0)printf(" (%s%d)",strcmp(data.tipoMem, "mmap")==0?"descriptor ":"", data.key);
            printf("\n");
        }
        p=nextM(p, *L);
    }
}