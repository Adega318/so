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



void allocate(char* Arg[], int numA, tListM *bloquesMem);
	bool allocateMalloc(char* Arg[], int numA, tListM* bloquesMem);
	bool allocateShared(char* Arg[], int numA, tListM* bloquesMem);
	bool allocateCreateshared (char* Arg[], int numA, tListM* bloquesMem);
	void * ObtenerMemoriaShmget (key_t clave, size_t tam, tNodeMem* data);
	bool allocateMmap (char* Arg[], int numA, tListM* bloquesMem);
	void do_AllocateMmap(char *arg[], tListM *LM);
	void * MapearFichero (char*, int, tListM*);
void deallocate(char* Arg[], int numA, tListM *bloquesMem);
	bool deallocateMalloc(char* Arg[], int numA, tListM* LM);
	bool deallocateShared(char* Arg[], int numA, tListM* LM);
	bool deallocateKey(char* Arg[], int numA, tListM* LM);
	void do_DeallocateDelkey (char *key);
	bool deallocateMmap(char* Arg[], int numA, tListM* LM);
	bool deallocateAddr(char* Arg[], int numA, tListM* LM, void* hex);
void io();
void memdump();
void memfill();
void memory(char* Arg[], int numA, tListM LM);
	void Do_pmap(void);
void recurse();

#endif