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
void IO(char* Arg[], int numA, tListM* LM);
	void do_I_O_read (char *Arg[]);
	ssize_t LeerFichero (char *f, void *p, size_t cont);
	void do_I_O_write(char* Arg[], int numA);
	ssize_t EscribirFichero (char *f, void *p, size_t cont, int overwrite);
void memdump(char* Arg[], int numA, tListM LM);
void memfill(char* Arg[], int numA, tListM LM);
	void LlenarMemoria (void *p, size_t cont, unsigned char byte);
void memory(char* Arg[], int numA, tListM LM);
	void Do_pmap(void);
void recurse(char* Arg[], int numA);
	void Recursiva (int n);

#endif