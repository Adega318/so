#include "comandP3.h"

void priority(char* Arg[], int numA){
    int value;
    id_t who;
    if(numA>1) who=(id_t)strtoul(Arg[1],NULL,10);
    else who=(id_t)getpid();

    if(numA>1 && numA>2){
        value=(int)strtoul(Arg[2],NULL,10);
        if(setpriority(PRIO_PROCESS, who, value)==-1){
            perror("error");
        }

    }else{
        value= getpriority(PRIO_PROCESS, who);
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

void execute(char* Arg[], int numA){
    int i=1;

    char* envp[TROCEO];
    char* auxVar, *aux;
    while(i<=numA-1 && *Arg[i]>='A' && *Arg[i]<='Z'){
        auxVar=getenv(Arg[i]);
        if(auxVar!=NULL){
            strcpy(aux, Arg[i]);
            strcat(aux, "=");
            strcat(aux, auxVar);
            envp[i-1]=aux;
        }else printf("error: %s not found\n", Arg[1]);
        i++;
    }
    envp[i-1]=NULL;

    int j=0;
    char* arg[TROCEO];
    if(i<=numA-1 && *Arg[i]!='@' && *Arg[i]!='&'){
        arg[j]=Ejecutable(Arg[i]);
        j++;
        i++;
    }else printf("error, program not obtained");

    while(i<=numA-1 && *Arg[i]!='@' && *Arg[i]!='&'){
        arg[j]=Arg[i];
        i++;
        j++;
    }arg[j]=NULL;

    if(i<=numA-1 && *Arg[i]=='@'){
		int priority= nice((int)strtoul(Arg[1]+1,NULL,10));
        if(priority==-1){
            perror("error");
        }
        i++;
    }
    if(i<=numA-1 && *Arg[i]=='&'){
        pid_t pid=fork();
        if(pid==0){
            execve(arg[0], arg, envp);
        }else if(pid>0){
            wait(NULL);
        }else perror("error");
    }else execve(arg[0], arg, envp);
}

char * Ejecutable (char *s){
	char path[PATH_MAX];
	static char aux2[PATH_MAX];
	struct stat st;
	char *p;

	if (s==NULL || (p=getenv("PATH"))==NULL) return s;

	if (s[0]=='/' || !strncmp (s,"./",2) || !strncmp (s,"../",3)) return s;       //is an absolute pathname

	strncpy (path, p, PATH_MAX);
	for (p=strtok(path,":"); p!=NULL; p=strtok(NULL,":")){
       sprintf (aux2,"%s/%s",p,s);
	   if (lstat(aux2,&st)!=-1) return aux2;
	}
	return s;
}