#include "comandP0.h"

void autores(char* Arg[], int numA){
    bool l=0,n=0;

    if(numA==1){
        n=1 ,l=1;
    }else if(strcmp(Arg[1],"-l")==0){
        l=1;
    }else if(strcmp(Arg[1],"-n")==0){
        n=1;
    }else{
		return;
    }

    if(n){printf("Enrique Adega Fernandez");} if(l && n){printf(" - ");} if(l){printf("e.adega@udc.es");}
    printf("\n");

    if(n){printf("Antonio Buceta Paz");} if(l && n){printf(" - ");} if(l){printf("antonio.buceta@udc.es");}
    printf("\n");
}

void pid(char* Arg[], int numA){
    if(numA!=1 && strcmp(Arg[1],"-p")==0){
		pid_t pid = getppid();
        printf("pid padre: %d\n", pid);
	}else{
		pid_t pid = getpid();
        printf("pid: %d\n", pid);
	}
}

void carpeta(char* Arg[], int numA){
    char p[PATH_MAX];

    if(numA==1){
        if(getcwd(p,sizeof(p))==NULL) perror("error");
        else printf("%s\n",p);
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

    if(numA==1){
        fullHist(*L);
    }else if(strcmp(Arg[1],"-c")==0){
        delList(L);
    }else{
        if(*Arg[1]=='-'){
            n=atoi(Arg[1]);
			n=n*-1;
            if(n>0){
                mostrarHistN(n, L);
            }
        }
    }
}
//Sub funciones del historial
void mostrarHistN(int n, tList *L){
    tPosL p = first(*L);
    for(int i = 1; (i<=n) && (p!=LNULL);i++){
        printf("\t- %d %s\n",i,getData(p, *L));
        p=next(p, *L);
    }
}
void fullHist(tList L){
    tPosL p= first(L);
    char* comand;
    int i=1;

    if (p!=LNULL)do{
        comand=getData(p, L);
        printf("\t- %d %s\n", i, comand);
        i++;
        p=next(p, L);
    }while(p!=LNULL);
}


void comando(char* Arg[], tList *L){
    int numHist=atoi(Arg[1]), numB;
    char* almacenamiento[TROCEO];
    tPosL p=findData(numHist, *L);

    if (p!=LNULL){
        char* I=malloc(sizeof(getData(p, *L)));
        strcpy(I, getData(p, *L));
        printf("Comando: %s\n", I);
        numB=trocear(I, almacenamiento);
        if(strcmp(almacenamiento[0], "comando")==0){
            printf("error: comando no premitido\n");
        }else{
            procesadoC(almacenamiento, numB, L);
        }
        free(I);
    }else printf("error: comando no encontrado\n");
    
}

void infosis(){
    struct utsname data;
    uname(&data);
    printf("Sidtema:  %s (%s)\nSO:  %s-%s-%s\n", data.nodename, data.machine, data.sysname, data.release, data.version);
}

void ayuda(char* Arg[], int numA){
    if(numA==1){
        printf("Lista de comandos:\n \t- autores\n \t- pid\n \t- carpeta\n \t- fecha\n \t- hist\n \t- comando\n \t- infosis\n \t- ayuda\n \t- create\n \t- stat\n \t- list\n \t- delete\n \t- deletetree\n");
    }else if(strcmp(Arg[1],"autores")==0){
        printf("autores [-l|-n]\timprime los nombres de los autores y sus login.\n\t-l: imprime solo los logins.\n\t-n: imprime solo los nombres.\n");
    }else if(strcmp(Arg[1],"pid")==0){
        printf("pid [-p]\timprime el pid del proceso ejecutando.\n\t-p: imprime el pid del proceso padre.\n");
    }else if(strcmp(Arg[1],"carpeta")==0){
        printf("carpeta [dir]\tcambia (o muestra) el directorio actual del shell.\n");
    }else if(strcmp(Arg[1],"fecha")==0){
        printf("fecha [-d][-h]\timprime la fecha y tiempo.\n\t-d: imprime solo la fecha.\n\t-h: imprime solo el tiempo.\n");
    }else if(strcmp(Arg[1],"hist")==0){
        printf("hist [-c|-N]\timprime el historial de comandos con su correspondiente número.\n\t-c: limpia el historial.\n\t-N: imprime los N primeros comandos.\n");
    }else if(strcmp(Arg[1],"comando")==0){
        printf("comando [N]\tejecuta el comando numero N del historial.\n");
    }else if(strcmp(Arg[1],"infosis")==0){
        printf("infosis\tda la imformación del sistema.\n");
    }else if(strcmp(Arg[1],"create")==0){
        printf("create [-f]\tcrea un archivo o un fichero(-f)\n");
    }else if(strcmp(Arg[1],"stat")==0){
        printf("stat [-long][-link][-acc] name1 name2 ..\tlista ficheros;\n\t-long: listado largo\n\t-acc: acesstime\n\t-link: si es enlace simbolico, path contenido\n");
    }else if(strcmp(Arg[1],"list")==0){
        printf("list [-reca] [-recb] [-hid][-long][-link][-acc] n1 n2 ..\tlista contenidos de directorios.\n\t-hid: incluye los ficheros ocultos\n\t-reca: recursivo(antes)\n\t-recb: recursivo (despues)\n\tparametros del stat\n");
    }else if(strcmp(Arg[1],"delete")==0){
        printf("delete name1 name2 ..\tborra ficheros o directorios vacios.\n");
    }else if(strcmp(Arg[1],"deletetee")==0){
        printf("deltree name1 name2 ..\tborra ficheros o directorios no vacios recursivamente.\n");
    }else {
    	printf("%s comando no encontrado\n", Arg[1]);
    }
}