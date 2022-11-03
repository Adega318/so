#ifndef COMAND_P1_H
#define COMAND_P1_H

#include "includes.h"

struct modCom{
	bool reca;
	bool recb;
	bool hid;
	bool lon;
	bool link;
	bool acc;
};

struct modCom ModComCreate();
struct modCom ModComSet(struct modCom modArg);
void create(char* Arg[], int numA);
void statfun(char* Arg[], int numA);
	void statprint (struct modCom modArg, char* pArg, char* Arg, struct stat stats);
	char LetraTF (mode_t m);
	char * ConvierteModo (mode_t m);
void list();
	void listrec(char* Arg, struct modCom modArg);
void delete(char *Arg[], int numA);
void deltree();

#endif