#ifndef COMAND_P3_H
#define COMAND_P3_H

#include "includes.h"

typedef struct jobNode *jobPointer;
struct jobNode{
    pid_t PID;
    struct tm dateAndTime;
    char *signal;
    int sig;
    char* comand;
    char* login;
    jobPointer next;
};
typedef jobPointer jobList;

//JOB LIST
void createJobList(jobList*);
void showJob(jobPointer);
bool addJob(struct jobNode, jobList*);
jobPointer getJob(pid_t, jobList*);
bool delJob(jobPointer, jobList*);
bool emptyJobList(jobList*);

void priority(char *[], int);
void showvar(char *[], int, char *[]);
    int BuscarVariable (char *, char *[]);
void changevar(char *[], int, char *[]);
    int CambiarVariable(char *, char *, char *[]);
void showenv(char *[], int, char *[]);
void forkShell(jobList*);
int execute(char* [], int, bool, jobList*);
    char* Ejecutable (char*);
void listjobs(jobList);
void deljobs(char* [], int, jobList*);
void job(char* [], int, jobList*);

#endif