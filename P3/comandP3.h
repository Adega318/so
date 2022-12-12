#ifndef COMAND_P3_H
#define COMAND_P3_H

#include "includes.h"

typedef struct jobNode *jobPointer;
struct jobNode{
    pid_t PID;
    struct tm dateAndTime;
    int signal;
    char* comand;
    char* login;
    int priority;
    jobPointer next;
};
typedef jobPointer jobList;

//JOB LIST
void createJobList(jobList*);
void showJob(jobPointer);
bool addJob(struct jobNode, jobList*);
    char *NombreSenal(int);
bool emptyJobList(jobList*);

void priority(char* [], int);
void showvar();
void changevar();
void showenv();
void forkShell();
void execute(char* [], int, bool, jobList*);
    char* Ejecutable (char*);
void listjobs(jobList);
void deljobs(jobList*);
void job();

#endif