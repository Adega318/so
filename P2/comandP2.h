#ifndef COMAND_P2_H
#define COMAND_P2_H

#include "includes.h"

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
    bool allocateMalloc(char* Arg[], int numA, struct modComMem modArg, tList* bloquesMem);
void deallocate();
void io();
void memdump();
void memfill();
void memory();
void recurse();

#endif