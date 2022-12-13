#include "comandP3.h"

//JOB LIST
bool createJobNode(jobPointer *P){
    *P=malloc(sizeof(struct jobNode));
    return *P!=NULL;
}

void createJobList(jobList* L){
    *L=NULL;
}

void showJob(jobPointer p){
    int sig;

    if(waitpid(p->PID, &sig, WNOHANG | WUNTRACED | WCONTINUED)==p->PID){
        free(p->signal);
        if(WIFEXITED(sig)){
            p->signal=strdup("FINISHED");
            p->sig=WEXITSTATUS(sig);
        }else if(WIFSIGNALED(sig)){
            p->signal=strdup("SIGNALED");
            p->sig=WTERMSIG(sig);
        }else if(WIFSTOPPED(sig)){
            p->signal=strdup("STOPED");
            p->sig=WSTOPSIG(sig);
        }else if(WIFCONTINUED(sig)){
            p->signal=strdup("ACTIVE");
            p->sig=0;
        }
    }

    printf("%d       %s p=%d", p->PID, p->login, getpriority(PRIO_PROCESS, p->PID));
    printf(" %d/%02d/%02d %02d:%02d:%02d ", p->dateAndTime.tm_year+1900, p->dateAndTime.tm_mon+1,
    p->dateAndTime.tm_mday, p->dateAndTime.tm_hour, p->dateAndTime.tm_min, p->dateAndTime.tm_sec);
    printf("%s (%03d) %s\n", p->signal, p->sig, p->comand);
}

bool addJob(struct jobNode N, jobList *L){
    jobPointer q,p;
    bool aux= 1;

    if(!createJobNode(&q)) aux=0;
    else{
        *q=N;
		q->next=NULL;
		if(*L==NULL){
            *L=q;
        }else{
			for (p = *L; p->next != NULL; p = p->next);
			p->next = q;
		}
    }
    return aux;
}

jobPointer getJob(pid_t PID, jobList *L){
    jobPointer p=*L;
    while (p!=NULL){
        if(p->PID==PID)return p;
        p=p->next;
    }return p;
    
}

bool emptyJobList(jobList *L){
    jobPointer p,q;
    q=*L;
    while (q!=NULL){
        p=q->next;
        free(q->comand);
        free(q->login);
        free(q->signal);
        free(q);
        q=p;
    }
}


//COMAND P3
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

void forkShell(jobList *L){
	pid_t pid;
	if ((pid=fork())==0){
        emptyJobList(L);
		printf ("ejecutando proceso %d\n", getpid());
	}else if (pid!=-1) waitpid (pid,NULL,0);
    else perror("error");
}

int execute(char* Arg[], int numA, bool program, jobList *L){
    int i, priority=-1, j=0, salida=0;
    bool env=false;
    if(program){
        i=0;
    }else i=1;

    //VAR
    char *auxVar, *aux=malloc(500), *aux2=malloc(100);
    char* envp[TROCEO];
    strcpy(aux2, "");
    if(numA>1){
        auxVar=getenv(Arg[i]);
        while(i<=numA-1 && auxVar!=NULL){
            env=true;
            if(auxVar!=NULL){
                strcat(aux2, Arg[i]);
                strcat(aux2, " ");

                strcpy(aux, Arg[i]);
                strcat(aux, "=");
                strcat(aux, auxVar);
                envp[j]=strdup(aux);
            }else printf("error: %s not found\n", Arg[1]);
            i++;
            j++;
            auxVar=getenv(Arg[i]);
        }
        envp[j]=NULL;
    }
    

    //COMAND AND ARGUMENTS
    char* arg[TROCEO];
    j=0;
    if(i<=numA-1 && *Arg[i]!='@' && *Arg[i]!='&'){
        strcpy(aux, aux2);
        free(aux2);
        strcat(aux, Arg[i]);
        arg[j]=Ejecutable(Arg[i]);
        j++;
        i++;
    }else printf("error, program not obtained");

    while(i<=numA-1 && *Arg[i]!='@' && *Arg[i]!='&'){
        strcat(aux, " ");
        strcat(aux, Arg[i]);
        arg[j]=Arg[i];
        i++;
        j++;
    }arg[j]=NULL;

    //PRIORITY
    if(i<=numA-1 && *Arg[i]=='@'){
        strcat(aux, " ");
        strcat(aux, Arg[i]);
		priority= nice((int)strtoul(Arg[1]+1,NULL,10));
        if(priority==-1) perror("error");
        i++;
    }

    //EJECUTION
    if(program){
        pid_t pid=fork();

        if(pid==0){
            if(env) j=execve(arg[0], arg, envp);
            else j=execv(arg[0], arg);
            if(j==-1)perror("error");
            salida=1;
            
        }else if(pid>0){
            if(i<=numA-1 && *Arg[i]=='&'){
                struct jobNode N;
                time_t rawtime=time(NULL);

                strcat(aux, " ");
                strcat(aux, Arg[i]);
                
                N.PID=pid;


                N.comand=strdup(aux);
                
                struct tm *lTime=localtime(&rawtime);
                N.dateAndTime=*lTime;
                
                N.signal=strdup("ACTIVE");

                N.sig=0;

                N.login=strdup(getlogin());

                addJob(N, L);
            }else waitpid(pid, NULL, 0);
            
        }else perror("error");
    }else{
        if(env) j=execve(arg[0], arg, envp);
        else j=execv(arg[0], arg);
        if(j==-1)perror("error");
    }
    if(env){
        i=0;
        while(envp[i]!=NULL){
            free(envp[i]);
            i++;
        }
    }
    free(aux);
    return salida;
}

//EXECUTE AUX
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

void listjobs(jobList L){
    jobPointer p=L;
    while (p!=NULL){
        showJob(p);
        p=p->next;
    }
}

void deljobs(jobList *L){
    emptyJobList(L);
}

void job(char *Arg[], int numA, jobList *L){
    bool fg=false, job=false;
    int i, sig;
    if(numA>2 && strcmp(Arg[1], "-fg")==0){
        i=2;
        fg=true;
    }
    if(numA>1 && strcmp(Arg[1], "-fg")!=0){
        i=1;
        job=true;
    }
    pid_t PID=(pid_t)strtoul(Arg[i],NULL,10);
    if(fg){
        jobPointer p=getJob(PID, L);
        if(waitpid(p->PID, &sig, 0)==p->PID){
            free(p->signal);
            if(WIFEXITED(sig)){
                p->signal=strdup("FINISHED");
                p->sig=WEXITSTATUS(sig);
            }else if(WIFSIGNALED(sig)){
                p->signal=strdup("SIGNALED");
                p->sig=WTERMSIG(sig);
            }else if(WIFSTOPPED(sig)){
                p->signal=strdup("STOPED");
                p->sig=WSTOPSIG(sig);
            }else if(WIFCONTINUED(sig)){
                p->signal=strdup("ACTIVE");
                p->sig=0;
            }
        }
        printf("Proceso %d terminado terminado normalmente. Valor devuelto %d\n", PID, sig);
    }else if(job){
        showJob(getJob(PID, L));
    }

}