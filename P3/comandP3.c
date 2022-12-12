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
    printf("%d       %s p=%d", p->PID, p->login, p->priority);
    printf(" %d/%02d/%02d %02d:%02d:%02d ", p->dateAndTime.tm_year+1900, p->dateAndTime.tm_mon+1,
    p->dateAndTime.tm_mday, p->dateAndTime.tm_hour, p->dateAndTime.tm_min, p->dateAndTime.tm_sec);
    char* signal= strsignal(p->signal);
    printf("%s (%03d) %s\n", signal, p->signal, p->comand);
    free(signal);
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

bool emptyJobList(jobList *L){
    jobPointer p,q;
    q=*L;
    while (q!=NULL){
        p=q->next;
        free(q->comand);
        free(q->login);
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

void forkShell(){
	pid_t pid;
	if ((pid=fork())==0){
/*		VaciarListaProcesos(&LP); Depende de la implementación de cada uno*/
		printf ("ejecutando proceso %d\n", getpid());
	}else if (pid!=-1) waitpid (pid,NULL,0);
    else perror("error");
}

void execute(char* Arg[], int numA, bool program, jobList *L){
    int i, priority=0;
    if(program){
        i=0;
    }else i=1;

    //VAR
    char* envp[TROCEO];
    char* auxVar, *aux, *aux2, *aux3=" ";
    if(numA>1){
        auxVar=getenv(Arg[i]);
        while(i<=numA-1 && auxVar!=NULL){
            if(auxVar!=NULL){
                strcpy(aux, Arg[i]);
                strcat(aux, "=");
                strcat(aux, auxVar);
                envp[i-1]=aux;
            }else printf("error: %s not found\n", Arg[1]);
            i++;
            auxVar=getenv(Arg[i]);
        }
    }
    envp[i-1]=NULL;

    //COMAND AND ARGUMENTS
    int j=0;
    char* arg[TROCEO];
    if(i<=numA-1 && *Arg[i]!='@' && *Arg[i]!='&'){
        aux=malloc(sizeof(Arg[i]));
        strcpy(aux, Arg[i]);
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
            if(execve(arg[0], arg, envp)==-1)perror("error");
        }else if(pid>0){
            if(i<=numA-1 && *Arg[i]=='&'){
                strcat(aux, " ");
                strcat(aux, Arg[i]);
                struct jobNode N;
                time_t rawtime=time(NULL);
                N.PID=pid;
                N.comand=malloc(sizeof(aux));
                strcpy(N.comand, aux);
                free(aux);
                j=1;
                while(arg[j]!=NULL){
                    strcat(N.comand, " ");
                    strcat(N.comand, arg[j]);
                    j++;
                }
                struct tm *lTime=localtime(&rawtime);
                N.dateAndTime=*lTime;
                if(N.priority=getpriority(PRIO_PROCESS, pid)==-1) perror("error");
                N.signal=kill(pid, 0);
                N.login=malloc(sizeof(getlogin()));
                strcpy(N.login, getlogin());
                addJob(N, L);
            }else waitpid(pid, NULL, 0);
            
        }else perror("error");
    }else if(execve(arg[0], arg, envp)==-1)perror("error");
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