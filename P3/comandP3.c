#include "comandP3.h"

void priority(char* Arg[], int numA){
    int which = PRIO_PROCESS, value;
    id_t who;
    if(numA>1) who=(id_t)strtoul(Arg[1],NULL,10);
    else who=(id_t)getpid();

    if(numA>1 && numA>2){
        value=(int)strtoul(Arg[2],NULL,10);
        if(setpriority(which, who, value)==-1){
            perror("error");
        }

    }else{
        value= getpriority(which, who);
        if(value==-1){
            perror("error");
        }else printf("Prioridad del proceso %d es %d\n", (int)who, value);
    }
}