#ifndef COMAND_P3_H
#define COMAND_P3_H

#include "includes.h"

void priority(char* [], int);
void showvar();
void changevar();
void showenv();
void forkShell();
void execute(char* [], int);
    char* Ejecutable (char*);
void listjobs();
void deljobs();
void job();

#endif