#ifndef FUNCION_H
#define FUNCION_H

#include "includes.h"
#include "list.h"
#include "listMem.h"
#include "comandP3.h"

//Funciones de control
int trocear(char *entrada, char* salida[]);
int procesadoC(char* [], int, tList*, tListM*, jobList*);

#endif