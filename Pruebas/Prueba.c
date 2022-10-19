#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <dirent.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/stat.h>



#define LNULL NULL
#define TROCEO 50
#define TMALLOC 4090

typedef struct tNode* tPosL;
struct tNode{
    char* comand;
    tPosL next;
};
typedef tPosL tList;

//Funciones de control
int trocear(char *entrada, char* salida[]);
int procesadoC(char* Arg[], int numA,tList* L);
void printC(char* Arg[], int numA);

//Funciones de comandos
//p0
void autores(char* Arg[], int numA);
void pid(char* Arg[], int numA);
void carpeta(char* Arg[], int numA);
void fecha(char* Arg[], int numA);
void hist(char* Arg[], int numA, tList *L);
	void mostrarHistN(int n, tList *L);
	void fullHist(tList L);
void comando(char* Arg[], int numA, tList *L);
void infosis(char* Arg[], int numA);
void ayuda(char* Arg[], int numA);
//p1
void create();
void statfun(char* Arg[], int numA);
	void statprint (bool lon, bool link, bool acc, char* pArg, char* Arg, struct stat stats);
	char LetraTF (mode_t m);
	char * ConvierteModo (mode_t m);
void list();
	void listrec(char* Arg, bool reca, bool recb, bool hid, bool lon, bool link, bool acc);
void delete();
void deltree();


//Funciones de operación de la lista
void createEmptyList(tList *L);
bool isEmptyList(tList L);
tPosL first(tList L);
tPosL last(tList L);
tPosL next(tPosL P, tList L);
tPosL previous(tPosL P, tList L);
char* getData(tPosL P, tList L);
tPosL findData(int I, tList L);
bool insertData(char *I, tList *L);
void delList( tList *L);















int main(){
    int salida=0, numA=0, c;
	char* entrada=malloc(TMALLOC);
    char* almacenamiento[TROCEO];
    tList L;
    
    createEmptyList(&L);

    while(salida==0){
        printf("\n--> ");
        if(scanf("%[^\n]s", entrada)>0) insertData(entrada, &L);
        numA=trocear(entrada,almacenamiento);
        salida=procesadoC(almacenamiento,numA, &L);
		strcpy(entrada, "");
		while((c = getchar()) != '\n' && c != EOF);
    }
	free(entrada);
    delList(&L);
    printf("exit successful\n\n");

    return 0;
}

























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

        }else if(strcmp(Arg[0],"create")==0){
            if(numA<=2){
                //
            }else printf("error: exceso de argumentos\n");

        }else if(strcmp(Arg[0],"stat")==0){
			statfun(Arg, numA);
        }else if(strcmp(Arg[0],"list")==0){
            list(Arg, numA);
        }else if(strcmp(Arg[0],"delete")==0){
            //
        }else if(strcmp(Arg[0],"deltree")==0){
            //
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
//p0
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
		return;
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
            }else printf("error: argumento incorrecto\n");
        }
    }
	/*
	else{
        strcpy(aux, Arg[1]);
        if(aux[0]=='-'){
            for(int i=1; i<=COMAND;i++) aux[i-1]=aux[i];
            n=atoi(aux);
            if(n>0){
                mostrarHistN(n, L);
            }else printf("error: argumento incorrecto\n");
        }
    }*/
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


void comando(char* Arg[], int numA, tList *L){
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

//p1
void statfun(char* Arg[], int numA){
	int i=1;
	bool lon=0, link=0, acc=0;
	struct stat stats;
	char p[PATH_MAX];
	
	while (numA>1 && i<numA && *Arg[i]=='-')
	{
		if(strcmp(Arg[i], "-long")==0) lon=1;
        else if(strcmp(Arg[i], "-link")==0) link=1;
        else if(strcmp(Arg[i], "-acc")==0) acc=1;
        else{
        	printf("error: argumento incorrecto");
            return;
    	}
		i++;
	}

	if(i<numA){
		for(i=i; i<numA; i++){
			if (lstat(Arg[i], &stats)==0){
				statprint(lon, link, acc, Arg[i], Arg[i], stats);
				//1	nlink	ino	2	3	mode	size name
			}else perror("error");
		}
	}else if(getcwd(p,sizeof(p))==NULL) {perror("error");}else printf("%s\n",p);
}

//subfunción de statfun
void statprint (bool lon, bool link, bool acc, char* pArg,char* Arg, struct stat stats){
	char* salida;
	int size=0;
	if(lon){
		struct tm *time;
		if(acc)time=gmtime(&stats.st_atim.tv_sec);
		else time=gmtime(&stats.st_mtim.tv_sec);
		printf("%d/%02d/%02d-%02d:%02d ", time->tm_year+1900, time->tm_mon+1, time->tm_mday, time->tm_hour+2, time->tm_min);
		printf("%3d ", (int)stats.st_nlink);
		printf("(%8d)\t", (int)stats.st_ino);
		printf("%s\t%s ", getpwuid(stats.st_uid)->pw_name, getgrgid(stats.st_gid)->gr_name);
		printf("%s ", ConvierteModo(stats.st_mode));
	}
	printf("%8d ", (int)stats.st_size);
	printf("%s", pArg);
	if(link && LetraTF(stats.st_mode)=='l'){
		salida=malloc(PATH_MAX);
		size= (int)readlink(Arg, salida, PATH_MAX);
		if (size>=0){
			printf(" --> %.*s",size, salida);
		}else perror("error1");
		free(salida);
	}
	printf("\n");
}

char LetraTF (mode_t m)
{
     switch (m&S_IFMT) { /*and bit a bit con los bits de formato,0170000 */
        case S_IFSOCK: return 's'; /*socket */
        case S_IFLNK: return 'l'; /*symbolic link*/
        case S_IFREG: return '-'; /* fichero normal*/
        case S_IFBLK: return 'b'; /*block device*/
        case S_IFDIR: return 'd'; /*directorio */ 
        case S_IFCHR: return 'c'; /*char device*/
        case S_IFIFO: return 'p'; /*pipe*/
        default: return '?'; /*desconocido, no deberia aparecer*/
     }
}
char * ConvierteModo (mode_t m)
{
    static char permisos[12];
    strcpy (permisos,"---------- ");
    
    permisos[0]=LetraTF(m);
    if (m&S_IRUSR) permisos[1]='r';    /*propietario*/
    if (m&S_IWUSR) permisos[2]='w';
    if (m&S_IXUSR) permisos[3]='x';
    if (m&S_IRGRP) permisos[4]='r';    /*grupo*/
    if (m&S_IWGRP) permisos[5]='w';
    if (m&S_IXGRP) permisos[6]='x';
    if (m&S_IROTH) permisos[7]='r';    /*resto*/
    if (m&S_IWOTH) permisos[8]='w';
    if (m&S_IXOTH) permisos[9]='x';
    if (m&S_ISUID) permisos[3]='s';    /*setuid, setgid y stickybit*/
    if (m&S_ISGID) permisos[6]='s';
    if (m&S_ISVTX) permisos[9]='t';
    
    return permisos;
}
//

void list(char* Arg[], int numA){
	int i=1;
	bool reca=0, recb=0, hid=0, lon=0, link=0, acc=0;
	char p[PATH_MAX];

	while (numA>1 && i<numA && *Arg[i]=='-'){
		if(strcmp(Arg[i], "-reca")==0) reca=1;
		else if(strcmp(Arg[i], "-recb")==0) recb=1;
		else if(strcmp(Arg[i], "-hid")==0) hid=1;
		else if(strcmp(Arg[i], "-long")==0) lon=1;
        else if(strcmp(Arg[i], "-link")==0) link=1;
        else if(strcmp(Arg[i], "-acc")==0) acc=1;
        else{
        	printf("error: argumento incorrecto");
            return;
    	}
		i++;
	}
	if(reca && recb) reca=0;

	if(i<numA) for(i=i; i<numA; i++) listrec(Arg[i], reca, recb, hid, lon, link, acc);
	else if(getcwd(p, sizeof(p))==NULL) {perror("error");}else printf("%s\n",p);
}

//subfunción de list
void listrec(char* Arg, bool reca, bool recb, bool hid, bool lon, bool link, bool acc){
	DIR* dp;
	struct dirent *dirp;
	struct stat stats;
	char* concat;
	char format;

	if(!reca && !recb) printf("****%s\n", Arg);
	dp=opendir(Arg);
	if(dp==NULL){} //perror("error");
	else{
		if (reca){
			listrec(Arg, 0, recb, hid, lon, link, acc);
		}

		while ((dirp=readdir(dp))!=NULL){
			if(((strcmp(dirp->d_name, ".")!=0 && strcmp(dirp->d_name, "..")!=0) || hid) && *dirp->d_name!='.'){
				concat=malloc(sizeof(Arg)+sizeof("/")+sizeof(dirp->d_name));
			
				strcpy(concat, Arg);
				if(strcmp(Arg, "/")!=0) strcat(concat, "/");
				strcat(concat, dirp->d_name);
				
				if (lstat(concat, &stats)==0){
					format=LetraTF(stats.st_mode);
				
					if(format=='d' && (reca || recb) && (strcmp(dirp->d_name, ".")!=0 && strcmp(dirp->d_name, "..")!=0)){
						listrec(concat, reca, recb, hid, lon, link, acc);
					}else if(!(reca || recb)) statprint(lon, link, acc, dirp->d_name, concat, stats);
					//1	nlink	ino	2	3	mode	size name
				}else perror("error");
				free(concat);
			}
		}if(closedir(dp)==-1) perror("error");
	}
}
//

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
        q->comand=malloc(255);
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

void delList( tList *L){
    tPosL p,q;

    p=*L;
    while(p!=LNULL){
        q=p->next;
		free(p->comand);
        free(p);
        p=q;
    }
    *L=LNULL;
}