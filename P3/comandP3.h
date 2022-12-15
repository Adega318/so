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
    char *NombreSenal(int);
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

struct SEN{
    char* nombre;
    int senal;
};

static struct SEN sigstrnum[]={   
	{"HUP", SIGHUP},
	{"INT", SIGINT},
	{"QUIT", SIGQUIT},
	{"ILL", SIGILL}, 
	{"TRAP", SIGTRAP},
	{"ABRT", SIGABRT},
	{"IOT", SIGIOT},
	{"BUS", SIGBUS},
	{"FPE", SIGFPE},
	{"KILL", SIGKILL},
	{"USR1", SIGUSR1},
	{"SEGV", SIGSEGV},
	{"USR2", SIGUSR2}, 
	{"PIPE", SIGPIPE},
	{"ALRM", SIGALRM},
	{"TERM", SIGTERM},
	{"CHLD", SIGCHLD},
	{"CONT", SIGCONT},
	{"STOP", SIGSTOP},
	{"TSTP", SIGTSTP}, 
	{"TTIN", SIGTTIN},
	{"TTOU", SIGTTOU},
	{"URG", SIGURG},
	{"XCPU", SIGXCPU},
	{"XFSZ", SIGXFSZ},
	{"VTALRM", SIGVTALRM},
	{"PROF", SIGPROF},
	{"WINCH", SIGWINCH}, 
	{"IO", SIGIO},
	{"SYS", SIGSYS},
/*senales que no hay en todas partes*/
#ifdef SIGPOLL
	{"POLL", SIGPOLL},
#endif
#ifdef SIGPWR
	{"PWR", SIGPWR},
#endif
#ifdef SIGEMT
	{"EMT", SIGEMT},
#endif
#ifdef SIGINFO
	{"INFO", SIGINFO},
#endif
#ifdef SIGSTKFLT
	{"STKFLT", SIGSTKFLT},
#endif
#ifdef SIGCLD
	{"CLD", SIGCLD},
#endif
#ifdef SIGLOST
	{"LOST", SIGLOST},
#endif
#ifdef SIGCANCEL
	{"CANCEL", SIGCANCEL},
#endif
#ifdef SIGTHAW
	{"THAW", SIGTHAW},
#endif
#ifdef SIGFREEZE
	{"FREEZE", SIGFREEZE},
#endif
#ifdef SIGLWP
	{"LWP", SIGLWP},
#endif
#ifdef SIGWAITING
	{"WAITING", SIGWAITING},
#endif
 	{NULL,-1},
};


#endif