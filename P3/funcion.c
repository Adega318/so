#include "funcion.h"
#include "comandP0.h"
#include "comandP1.h"
#include "comandP2.h"
#include "comandP3.h"

//Troceado de la cadena
int trocear(char *entrada, char* salida[]){
	int i=1;
	if((salida[0]=strtok(entrada," \n\t"))==NULL) return 0;
	while((salida[i]=strtok(NULL," \n\t"))!=NULL) i++;
	return i;
}

//Procesado de comandos
int procesadoC(char* Arg[], int numA, char* envp[], tList* L, tListM* listMem, jobList *jobL){
	if(numA>0){
		if(strcmp(Arg[0],"autores")==0){
			autores(Arg, numA);
		}else if(strcmp(Arg[0],"pid")==0){
			pid(Arg, numA);
		}else if(strcmp(Arg[0],"carpeta")==0){
			carpeta(Arg, numA);
		}else if(strcmp(Arg[0],"fecha")==0){
			fecha(Arg, numA);
		}else if(strcmp(Arg[0],"hist")==0){
			hist(Arg, numA, L);
		}else if(strcmp(Arg[0],"comando")==0){
			if(numA==1){
				hist(Arg, 1, L);
			}else comando(Arg, L, listMem, jobL, envp);
		}else if(strcmp(Arg[0],"infosis")==0){
			infosis();
		}else if(strcmp(Arg[0],"ayuda")==0){
			ayuda(Arg, numA);
		}else if(strcmp(Arg[0],"create")==0){
			create(Arg, numA);
		}else if(strcmp(Arg[0],"stat")==0){
			statfun(Arg, numA);
		}else if(strcmp(Arg[0],"list")==0){
			list(Arg, numA);
		}else if(strcmp(Arg[0],"delete")==0){
			delete(Arg, numA);
		}else if(strcmp(Arg[0],"deltree")==0){
			deltree(Arg, numA);
		}else if(strcmp(Arg[0],"allocate")==0){
			allocate(Arg, numA, listMem);
		}else if(strcmp(Arg[0],"deallocate")==0){
			deallocate(Arg, numA, listMem);
		}else if(strcmp(Arg[0],"i-o")==0){
			IO(Arg, numA, listMem);
		}else if(strcmp(Arg[0],"memdump")==0){
			memdump(Arg, numA, *listMem);
		}else if(strcmp(Arg[0],"memfill")==0){
			memfill(Arg, numA, *listMem);
		}else if(strcmp(Arg[0],"memory")==0){
			memory(Arg, numA, *listMem);
		}else if(strcmp(Arg[0],"recurse")==0){
			recurse(Arg, numA);
		}else if(strcmp(Arg[0],"priority")==0){
			priority(Arg, numA);
		}else if(strcmp(Arg[0],"showvar")==0){
			showvar(Arg, numA, envp);
		}else if(strcmp(Arg[0],"changevar")==0){
			changevar(Arg, numA, envp);
		}else if(strcmp(Arg[0],"showenv")==0){
			showenv(Arg, numA, envp);
		}else if(strcmp(Arg[0],"fork")==0){
			forkShell(jobL);
		}else if(strcmp(Arg[0],"execute")==0){
			execute(Arg, numA, false, jobL);
		}else if(strcmp(Arg[0],"listjobs")==0){
			listjobs(*jobL);
		}else if(strcmp(Arg[0],"deljobs")==0){
			deljobs(Arg, numA, jobL);
		}else if(strcmp(Arg[0],"job")==0){
			job(Arg, numA, jobL);
		}else if(strcmp(Arg[0],"fin")==0 || strcmp(Arg[0],"bye")==0 || strcmp(Arg[0],"salir")==0){
			return 1;
		}else return execute(Arg, numA, true, jobL);
	}
	
	return 0;
}