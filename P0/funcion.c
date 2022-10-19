#include "funcion.h"

//Troceado de la cadena
int trocear(char *entrada, char* salida[]){
    int i=1;
    if((salida[0]=strtok(entrada," \n\t"))==NULL) return 0;
    while((salida[i]=strtok(NULL," \n\t"))!=NULL) i++;
    return i;
}

//Procesado de comandos
int procesadoC(char* Arg[], int numA,tList* L){
    if(numA>0){
        if(strcmp(Arg[0],"autores")==0){
            if(numA<=2){
                autores(Arg, numA);
            }else printf("error: exceso de argumentos\n");

        }else if(strcmp(Arg[0],"pid")==0){
            if(numA<=2){
                pid(Arg, numA);
            }else printf("error: exceso de argumentos\n");

        }else if(strcmp(Arg[0],"carpeta")==0){
            if(numA<=2){
                carpeta(Arg, numA);
            }else printf("error: exceso de argumentos\n");
        }else if(strcmp(Arg[0],"fecha")==0){
            if(numA<=2){
                fecha(Arg, numA);
            }else printf("error: exceso de argumentos\n");

        }else if(strcmp(Arg[0],"hist")==0){
            if(numA<=2){
                hist(Arg, numA, L);
            }else printf("error: exceso de argumentos\n");

        }else if(strcmp(Arg[0],"comando")==0){
            if(numA==2){
                comando(Arg, numA, L);
            }else if(numA==1){
                printf("error: introduce una N\n");
            }else printf("error: exceso de argumentos\n");

        }else if(strcmp(Arg[0],"infosis")==0){
            if(numA<2){
                infosis(Arg, numA);
            }else printf("error: exceso de argumentos\n");

        }else if(strcmp(Arg[0],"ayuda")==0){
            if(numA<=2){
                ayuda(Arg, numA);
            }else printf("error: exceso de argumentos\n");

        }else if(strcmp(Arg[0],"fin")==0 || strcmp(Arg[0],"bye")==0 || strcmp(Arg[0],"salir")==0){
            if(numA<2){
                return 1;
            }else printf("error: exceso de argumentos\n");

        }else printf("error: comando no reconozido\n");
    }
    
    return 0;
}

//Mostrar comando
void printC(char* Arg[], int numA){
    for(int i=0; i<numA;i++){
        printf("%s ",Arg[i]);
    }
    printf("\n");
}



//FUNCIONES DE COMANDOS
void autores(char* Arg[], int numA){
    bool l=0,n=0;

    if(numA==1){
        n=1 ,l=1;
    }else if(strcmp(Arg[1],"-l")==0){
        l=1;
    }else if(strcmp(Arg[1],"-n")==0){
        n=1;
    }else{
        printf("error: argumento incorrecto\n");
    }

    if(n){printf("Enrique Adega Fernandez");} if(l && n){printf(" - ");} if(l){printf("e.adega@udc.es");}
    printf("\n");

    if(n){printf("Antonio Buceta Paz");} if(l && n){printf(" - ");} if(l){printf("antonio.buceta@udc.es");}
    printf("\n");
}

void pid(char* Arg[], int numA){
    bool p=0;

    if(numA==1){
    }else if(strcmp(Arg[1],"-p")==0){
        p=1;
    }else{
        printf("error: argumento incorrecto\n");
    }

    if(!p){
        pid_t pid = getpid();
        printf("pid: %d\n", pid);
    }else if(p){
        pid_t pid = getppid();
        printf("pid padre: %d\n", pid);
    }


}

void carpeta(char* Arg[], int numA){
    char p[COMAND];

    if(numA==1){
        if(getcwd(p,COMAND)==NULL) perror("error");
        else printf("Estas en: %s\n",p);
    }else if(chdir(Arg[1])==-1) perror("error");
}

void fecha(char* Arg[], int numA){
    time_t t;
    struct tm *tm;
    time(&t);
    tm = localtime(&t);
    bool h=0, d=0;

    if(tm!=NULL){
        if(numA==1){
            h=1, d=1;
        }else if(strcmp(Arg[1],"-h")==0){
            h=1;
        }else if(strcmp(Arg[1],"-d")==0){
            d=1;
        }else {
            printf("error: argumento incorrecto\n");
        }

        if(h){
            printf("Horas: %02d:%02d:%02d\n", tm->tm_hour, tm->tm_min, tm->tm_sec);
        }
        if(d){
            printf("Fecha: %02d/%02d/%d\n", tm->tm_mday, tm->tm_mon+1, tm->tm_year+1900);
        }
    }else perror("error");
}

void hist(char* Arg[], int numA, tList *L){
    int n=0;
    char aux[TROCEO];

    if(numA==1){
        fullHist(*L);
    }else if(strcmp(Arg[1],"-c")==0){
        delHist(L);
    }else{
        strcpy(aux, Arg[1]);
        if(aux[0]=='-'){
            for(int i=1; i<=TROCEO;i++) aux[i-1]=aux[i];
            n=atoi(aux);
            if(n>0){
                mostrarHistN(n, L);
            }else printf("error: argumento incorrecto\n");
        }
    }
}
//Sub funciones del historial
void mostrarHistN(int n, tList *L){
    tPosL p = first(*L);
    for(int i = 1; (i<=n) && (p!=LNULL);i++){
        printf("\t- %d %s",i,getData(p, *L));
        p=next(p, *L);
    }
}
void fullHist(tList L){
    tPosL p= first(L);
    char* comand;
    int i=1;

    if (p!=LNULL)do{
        comand=getData(p, L);
        printf("\t- %d %s", i, comand);
        i++;
        p=next(p, L);
    }while(p!=LNULL);
}


void comando(char* Arg[], int numA, tList *L){
    int numHist=atoi(Arg[1]), numB;
    char* almacenamiento[TROCEO];
    tPosL p=findData(numHist, *L);

    if (p!=LNULL){
        char* I=malloc(sizeof(getData(p, *L)));;
        strcpy(I, getData(p, *L));
        printf("Comando: %s", I);
        numB=trocear(I, almacenamiento);
        if(strcmp(almacenamiento[0], "comando")==0){
            printf("error: comando no premitido\n");
        }else{
            procesadoC(almacenamiento, numB, L);
        }
        free(I);
    }else printf("error: comando no encontrado\n");
    
}

void infosis(char* Arg[], int numA){
    struct utsname data;
    uname(&data);
    printf("Sidtema:  %s (%s)\nSO:  %s-%s-%s\n", data.nodename, data.machine, data.sysname, data.release, data.version);
}

void ayuda(char* Arg[], int numA){
    if(numA==1){
        printf("Lista de comandos:\n \t- autores\n \t- pid\n \t- carpeta\n \t- fecha\n \t- hist\n \t- comando\n \t- infosis\n \t- ayuda\n");
    }else if(strcmp(Arg[1],"autores")==0){
        printf("autores [-l][-n]: imprime los nombres de los autores y sus login.\n\t-l: imprime solo los logins.\n\t-n: imprime solo los nombres.\n");
    }else if(strcmp(Arg[1],"pid")==0){
        printf("pid [-p]: imprime el pid del proceso ejecutando.\n\t-p: imprime el pid del proceso padre.\n");
    }else if(strcmp(Arg[1],"carpeta")==0){
        printf("carpeta [direción]: cambia la dicerión de trabajo a la entregada, si no se entrega direción muestra la actual.\n");
    }else if(strcmp(Arg[1],"fecha")==0){
        printf("fecha [-d][-h]: imprime la fecha y tiempo.\n\t-d: imprime solo la fecha.\n\t-h: imprime solo el tiempo.\n");
    }else if(strcmp(Arg[1],"hist")==0){
        printf("hist [-c][-N]: imprime el historial de comandos con su correspondiente número.\n\t-c: limpia el historial.\n\t-N: imprime los N primeros comandos.\n");
    }else if(strcmp(Arg[1],"comando")==0){
        printf("comando N: ejecuta el comando numero N del historial.\n");
    }else if(strcmp(Arg[1],"infosis")==0){
        printf("infosis: da la imformación del sistema.\n");
    }else {
        printf("error: argumento incorrecto\n");
    }
}



//FUNCIONES DE LA LISTA
bool createNode(tPosL *P){
    *P=malloc(sizeof(struct tNode));
    return *P!=LNULL;
}

void createEmptyList(tList *L){
    *L=LNULL;
}

bool isEmptyList(tList L){
    return L==LNULL;
}

tPosL first(tList L){
    return L;
}

tPosL last(tList L){
    tPosL p;
    for(p=L; p->next!=LNULL; p=p->next);
    return p;
}

tPosL next(tPosL P, tList L){
    return P->next;
}

tPosL previous(tPosL P, tList L){
    tPosL p;
    if(P==L) p=LNULL;
    else for(p=L; p->next!=P; p=p->next);
    return p;
}

tPosL findData(int I, tList L){
    tPosL p=L;
    int i=1;

    if (isEmptyList(L)) p=LNULL;
    else for(i=1; i!=I; i++) p=p->next;
    return p;   
}

bool insertData(char* I,tList *L){
    tPosL q,p;
    bool aux= 1;

    if(!createNode(&q)) aux=0;
    else{
        strcpy(q->comand, I);
        q->next=LNULL;
        if(*L==LNULL)*L=q;
        else{
            for (p = *L; p->next != LNULL; p = p->next);
            p->next = q;

        }
    }
    return aux;
}

char* getData(tPosL P, tList L){
    return P->comand;
}

void delHist( tList *L){
    tPosL p,q;

    p=*L;
    while(p!=LNULL){
        q=p->next;
        free(p);
        p=q;
    }
    *L=LNULL;
}