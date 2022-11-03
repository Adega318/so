#include "comandP2.h"
#include "list.h"

struct modCom ModComCreate(){
	struct modCom modArg;
	modArg.malloc=0, modArg.createShared=0, modArg.mmap=0, modArg.delKey=0, modArg.addr=0;
	modArg.read=0, modArg.o=0, modArg.blocks=0, modArg.funcs=0, modArg.vars=0, modArg.all=0;
	modArg.pmap=0;
	return modArg;
}

void allocate(char* Arg[], int numA, tList *bloquesMem){
	struct modCom modArg=ModComCreate();
	bool standard=1;
	bool standardPlus=0;

	if(numA>1 && *Arg[1]=='-')
	{
		standard=0;
		if(strcmp(Arg[1], "-malloc")==0) modArg.malloc=1;
		else if(strcmp(Arg[1], "-createshared")==0) modArg.createShared=1;
		else if(strcmp(Arg[1], "-shared")==0) modArg.shared=1;
		else if(strcmp(Arg[1], "-mmap")==0) modArg.malloc=1;
		else{ standard=1;}
	}

	if(modArg.malloc){
		if(numA>3 && )
	}

	if(standard){
		printf("******Lista de bloques asignados ");
		if(standardPlus) printf("%s ", Arg[1]);
		printf("para el proceso %d", getpid());
	}
}