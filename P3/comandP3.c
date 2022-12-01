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

void forkShell(){
	pid_t pid;
	if ((pid=fork())==0){
/*		VaciarListaProcesos(&LP); Depende de la implementación de cada uno*/
		printf ("ejecutando proceso %d\n", getpid());
	}else if (pid!=-1) waitpid (pid,NULL,0);
    else perror("error");
}

/*void execute(char* Arg[], int numA){
    char* almaaux[TROCEO-1];
    strcpy(almaaux, Arg+sizeof(Arg[0]));
}

char * Ejecutable (char *s){
	char path[MAXNAME];
	static char aux2[MAXNAME];
	struct stat st;
	char *p;

	if (s==NULL || (p=getenv("PATH"))==NULL) return s;

	if (s[0]=='/' || !strncmp (s,"./",2) || !strncmp (s,"../",3)) return s;       //is an absolute pathname

	strncpy (path, p, MAXNAME);
	for (p=strtok(path,":"); p!=NULL; p=strtok(NULL,":")){
       sprintf (aux2,"%s/%s",p,s);
	   if (lstat(aux2,&st)!=-1) return aux2;
	}
	return s;
}

int OurExecvpe(const char *file, char *const argv[], char *const envp[]){
   return (execve(Ejecutable(file) ,argv, envp));
}*/