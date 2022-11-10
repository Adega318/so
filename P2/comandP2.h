#ifndef COMAND_P2_H
#define COMAND_P2_H

#include "includes.h"
#include "listMem.h"

struct modComMem
{
    bool malloc;
    bool shared;
    bool createShared;
    bool mmap;
    bool delKey;
    bool addr;
    bool read;
    bool o;
    bool blocks;
    bool funcs;
    bool vars;
    bool all;
    bool pmap;
};



void allocate();
    bool allocateMalloc(char* Arg[], int numA, tListM* bloquesMem);
    bool allocateShared(char* Arg[], int numA, tListM* bloquesMem);
    bool allocateCreateshared (char* Arg[], int numA, tListM* bloquesMem);
    void * ObtenerMemoriaShmget (key_t clave, size_t tam, tNodeMem* Mnode);
void deallocate();
void io();
void memdump();
void memfill();
void memory();
void recurse();

#endif