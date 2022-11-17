#include "comandP2.h"
#include "listMem.h"
int g1=0, g2=0, g3=0;

struct modComMem ModComMemCreate(){
	struct modComMem modArg;
	modArg.malloc=0, modArg.createShared=0, modArg.shared=0, modArg.mmap=0, modArg.delKey=0, modArg.addr=0;
	modArg.read=0, modArg.o=0, modArg.blocks=0, modArg.funcs=0, modArg.vars=0, modArg.all=0;
	modArg.pmap=0;
	return modArg;
}


//ALLOCATE
void allocate(char* Arg[], int numA, tListM *bloquesMem){
	struct modComMem modArg=ModComMemCreate();
	bool standardPlus=0;
	char *argChop=NULL;

	if(numA>1 && *Arg[1]=='-')
	{
		if(strcmp(Arg[1], "-malloc")==0) modArg.malloc=1;
		else if(strcmp(Arg[1], "-createshared")==0) modArg.createShared=1;
		else if(strcmp(Arg[1], "-shared")==0) modArg.shared=1;
		else if(strcmp(Arg[1], "-mmap")==0) modArg.mmap=1;
	}

	if(modArg.malloc) standardPlus=allocateMalloc(Arg, numA, bloquesMem);
	else if(modArg.shared) standardPlus=allocateShared(Arg, numA, bloquesMem);
	else if(modArg.createShared) standardPlus=allocateCreateshared(Arg, numA, bloquesMem);
	else if(modArg.mmap) standardPlus=allocateMmap(Arg, numA, bloquesMem);

	if(numA==1 || standardPlus){
		printf("******Lista de bloques asignados ");
		if(standardPlus){
			argChop= Arg[1]+1;
			printf("%s ", argChop);
		}
		printf("para el proceso %d\n", getpid());
		printType(argChop, *bloquesMem);
	}
}

//ALLOCATE_MALLOC
bool allocateMalloc(char* Arg[], int numA, tListM* bloquesMem){
	if(numA==2 || (numA>2 && *Arg[2]=='-')) return 1;
	else{
		int size= (int)strtoul(Arg[2],NULL,10);
		void* hex=NULL;
		if(size!=ULONG_MAX) hex=malloc(size); else perror("error");

		if(hex==NULL) printf("No se asignan bloques de 0 bytes");
		else{
			tNodeMem data;
			time_t t;
			data.creationTime=time(&t);
			data.hex=hex;
			data.space=size;
			data.tipoMem=malloc(sizeof("malloc"));
			strcpy(data.tipoMem, "malloc");
			insertDataM(data, bloquesMem);
			printf("Asignados %d bytes en %p\n", size, hex);
		}
	}return 0;
}

//ALLOCATE_SHARED
bool allocateShared(char* Arg[], int numA, tListM* bloquesMem){
	if(numA==2 || (numA>2 && *Arg[2]=='-')) return 1;
	else{
		tNodeMem data;
		void *hex;
		key_t key= (key_t)strtoul(Arg[2],NULL,10);
		hex=ObtenerMemoriaShmget(key, 0, &data);
		if(hex==NULL)printf("No se asignan bloques de 0 bytes\n");
		else{
			data.hex=hex;
			insertDataM(data, bloquesMem);
			printf("Memoria compartida de clave %lu  en %p\n", (unsigned long) key, data.hex);
		}
	}return 0;
}

bool allocateCreateshared (char* Arg[], int numA, tListM* bloquesMem){
	if(numA==2 || (numA>2 && *Arg[2]=='-') || (numA>3 && *Arg[3]=='-')) return 1;
	else {
		key_t cl;
		size_t size;
		void *hex;

		cl=(key_t)  strtoul(Arg[2],NULL,10);
		size=(size_t) strtoul(Arg[3],NULL,10);
		if (size==0) {
			printf ("No se asignan bloques de 0 bytes\n");
			return 0;
		}
		tNodeMem data;
		hex=ObtenerMemoriaShmget(cl,size, &data);
		if ((hex!=NULL)){
			insertDataM(data, bloquesMem);
			printf ("Asignados %lu bytes en %p\n",(unsigned long) size, data.hex);
		}
		else printf ("Imposible asignar memoria compartida clave %lu:%s\n",(unsigned long) cl,strerror(errno));
	}return 0;
}

void* ObtenerMemoriaShmget (key_t clave, size_t tam, tNodeMem* Mnode){
	void * p;
	int aux,id,flags=0777;
	struct shmid_ds s;

	if (tam)     /*tam distito de 0 indica crear */
		flags=flags | IPC_CREAT | IPC_EXCL;
	if (clave==IPC_PRIVATE)  /*no nos vale*/
		{errno=EINVAL; return NULL;}
	if ((id=shmget(clave, tam, flags))==-1)
		return (NULL);
	if ((p=shmat(id,NULL,0))==(void*) -1){
		aux=errno;
		if (tam)
			shmctl(id,IPC_RMID,NULL);
		errno=aux;
		return (NULL);
	}
	shmctl (id,IPC_STAT,&s);
	Mnode->creationTime=s.shm_ctime;
	Mnode->hex=p;
	Mnode->space=s.shm_segsz;
	Mnode->key=clave;
	Mnode->tipoMem=malloc(sizeof("shared"));
	strcpy(Mnode->tipoMem, "shared");

	return p;
}

//ALLOCATE_MMAP
bool allocateMmap (char* Arg[], int numA, tListM* bloquesMem){
	if(numA==2 || (numA>2 && *Arg[2]=='-') || (numA>3 && *Arg[3]=='-')) { return 1;}
	else{
		if(numA>3 && strlen(Arg[3])>3){printf("Permisos rechazados\n"); return 0;}
		do_AllocateMmap(Arg, bloquesMem);
	}return 0;
}


void do_AllocateMmap(char *arg[], tListM *LM){ 
	char *perm;
	void *p;
	int protection=0;
	if ((perm=arg[3])!=NULL && strlen(perm)<4) {
		if (strchr(perm,'r')!=NULL) protection|=PROT_READ;
		if (strchr(perm,'w')!=NULL) protection|=PROT_WRITE;
		if (strchr(perm,'x')!=NULL) protection|=PROT_EXEC;
	}
	if ((p=MapearFichero(arg[2],protection, LM))==NULL){
		perror ("Imposible mapear fichero");
	}else{
		printf ("fichero %s mapeado en %p\n", arg[2], p);
	}
}

void * MapearFichero (char * fichero, int protection, tListM* LM){
	int df, map=MAP_PRIVATE,modo=O_RDONLY;
	struct stat s;
	void *p;
	time_t t=time(NULL);

	if (protection&PROT_WRITE) modo=O_RDWR;
	if (stat(fichero,&s)==-1 || (df=open(fichero, modo))==-1) return NULL;
	if ((p=mmap (NULL,s.st_size, protection,map,df,0))==MAP_FAILED) return NULL;

	tNodeMem data;
	localtime(&t);
	data.creationTime=t;
	data.hex=p;
	data.space=s.st_size;
	data.key=df;
	data.tipoMem=malloc(sizeof(fichero));
	strcpy(data.tipoMem, fichero);
	insertDataM(data, LM);

	return p;
}


//DEALLOCATE
void deallocate(char* Arg[], int numA, tListM *LM){
	struct modComMem modArg=ModComMemCreate();
	bool standardPlus=0;
	char *argChop=NULL;

	if(numA>1 && *Arg[1]=='-')
	{
		if(strcmp(Arg[1], "-malloc")==0) modArg.malloc=1;
		else if(strcmp(Arg[1], "-delkey")==0) modArg.delKey=1;
		else if(strcmp(Arg[1], "-shared")==0) modArg.shared=1;
		else if(strcmp(Arg[1], "-mmap")==0) modArg.mmap=1;
	}else if(numA>1) modArg.addr=1;

	if(modArg.malloc) standardPlus=deallocateMalloc(Arg, numA, LM);
	if(modArg.delKey) standardPlus=deallocateKey(Arg, numA, LM);
	if(modArg.shared) standardPlus=deallocateShared(Arg, numA, LM);
	if(modArg.mmap) standardPlus=deallocateMmap(Arg, numA, LM);
	if(modArg.addr) deallocateAddr(Arg, numA, LM, NULL);

	if(numA==1 || standardPlus){
		printf("******Lista de bloques asignados ");
		if(standardPlus){
			argChop= Arg[1]+1;
			printf("%s ", argChop);
		}
		printf("para el proceso %d\n", getpid());
		printType(argChop, *LM);
	}
}

//DEALLOCATE_MALLOC
bool deallocateMalloc(char* Arg[], int numA, tListM* LM){
	if(numA==2 || (numA>2 && *Arg[2]=='-')) return 1;
	else{
		int size= (int)strtoul(Arg[2],NULL,10);
		tPosLM p;
		tNodeMem q;
		if(size!=ULONG_MAX){
			p=findSizeInType(size, Arg[1]+1, *LM);
			if(p!=NULL){
				q=getDataM(p, *LM);
				free(q.hex);
				delPos(p, LM);
			}else printf("No hay bloque de ese tamano asignado con malloc\n");
		}
	}return 0;
}

//DEALLOCATE_SHARED
bool deallocateShared(char* Arg[], int numA, tListM* LM){
	if(numA==2 || (numA>2 && *Arg[2]=='-')) return 1;
	else{
		tPosLM p=NULL;
		tNodeMem q;
		key_t clave= (key_t)  strtoul(Arg[2],NULL,10);

		p=finkey(clave, *LM);
		if(p!=NULL){
			q= getDataM(p, *LM);
			if(shmdt(q.hex)==-1) perror("error");
			else delPos(p, LM);
		}else printf("No hay bloque de esa clave mapeado en el proceso\n");
		
	}return 0;
}

//DEALLOCATE_KEY
bool deallocateKey(char* Arg[], int numA, tListM* LM){
	if(numA==2 || (numA>2 && *Arg[2]=='-')) return 1;
	else{
		do_DeallocateDelkey(Arg[2]);
		
	}return 0;
}

void do_DeallocateDelkey (char *key){
	key_t clave;
	int id;

	if (key==NULL || (clave=(key_t) strtoul(key,NULL,10))==IPC_PRIVATE){
		printf ("      delkey necesita clave_valida\n");
		return;
	}
	if ((id=shmget(clave,0,0666))==-1){
		perror ("shmget: imposible obtener memoria compartida");
		return;
	}
	if (shmctl(id,IPC_RMID,NULL)==-1) perror ("shmctl: imposible eliminar memoria compartida\n");
}

//DEALLOCATE_MMAP
bool deallocateMmap(char* Arg[], int numA, tListM* LM){
	if(numA==2 || (numA>2 && *Arg[2]=='-')) return 1;
	else{
		if(!isEmptyListM(*LM)){
			tPosLM p=*LM;
			tNodeMem d;
			bool sal=false;
			while(p!=NULL && !sal){
				d= getDataM(p, *LM);
				if(strcmp(d.tipoMem, Arg[2])==0){
					sal= true;
				}else p=nextM(p, *LM);
			}
			if(sal){
				munmap(d.hex, d.space);
				delPos(p, LM);
				return 0;
			}
		}printf("Fichero %s no mapeado", Arg[2]);
	}return 0;
}

//DEALLOCATE_ADDR
bool deallocateAddr(char* Arg[], int numA, tListM* LM, void* hex){
	if(numA>1 || numA==-1){
		if(numA>1){
			if(*Arg[1]=='0' && *(Arg[1]+1)=='x') hex= (int*)strtol(Arg[1]+2, NULL, 16);
			else hex= (int*)strtol(Arg[1], NULL, 16);
		}
		tPosLM p=findHex(hex, *LM);
		tNodeMem d;
		
		if(p!=NULL){
			d=getDataM(p, *LM);
			if(strcmp(d.tipoMem, "malloc")==0){
				free(d.hex);
				delPos(p, LM);
			}else if(strcmp(d.tipoMem, "shared")==0){
				if(shmdt(d.hex)==-1) perror("error");
				else delPos(p, LM);
			}else{
				munmap(d.hex, d.space);
				delPos(p, LM);
			}
		}else printf("Direccion %s no asignada con malloc, shared o mmap\n", Arg[1]);
	}
}


//I-O
void IO(char* Arg[], int numA, tListM* LM){
	if(numA>4){
		if(strcmp(Arg[1], "-read")==0){
			do_I_O_read(Arg);
		}else if(strcmp(Arg[1], "-write")==0){
			do_I_O_write(Arg, numA);
		}
	}
}

//I-O_READ
void do_I_O_read (char *Arg[]){
	void *p;
	size_t cont=-1;
	ssize_t n;
	if (Arg[1]==NULL || Arg[2]==NULL){
		printf ("faltan parametros\n");
		return;
	}
	if(*Arg[3]=='0' && *(Arg[3]+1)=='x') p= (int*)strtol(Arg[3]+2, NULL, 16);
	else p= (int*)strtol(Arg[3], NULL, 16);

	if (Arg[4]!=NULL) cont=(size_t) atoll(Arg[4]);

	if ((n=LeerFichero(Arg[2],p,cont))==-1) perror ("Imposible leer fichero");
	else printf ("leidos %lld bytes de %s en %p\n", n,Arg[2],p);
}

ssize_t LeerFichero (char *f, void *p, size_t cont){
   struct stat s;
   ssize_t  n;  
   int df,aux;

   if (stat (f,&s)==-1 || (df=open(f,O_RDONLY))==-1)
	return -1;     
   if (cont==-1)   /* si pasamos -1 como bytes a leer lo leemos entero*/
	cont=s.st_size;
   if ((n=read(df,p,cont))==-1){
	aux=errno;
	close(df);
	errno=aux;
	return -1;
   }
   close (df);
   return n;
}

//I-O_WRITE
void do_I_O_write(char* Arg[], int numA){
	void* hex;
	ssize_t size;
	int desplazamiento=0;
	if(numA>5 && strcmp(Arg[2], "-o")==0){
		desplazamiento=1;
	}

	if(*Arg[3+desplazamiento]=='0' && *(Arg[3+desplazamiento]+1)=='x') hex= (int*)strtol(Arg[3+desplazamiento]+2, NULL, 16);
	else hex= (int*)strtol(Arg[3+desplazamiento], NULL, 16);
	size_t cont= (size_t)strtoul(Arg[4+desplazamiento],NULL,10);

	size=EscribirFichero(Arg[2+desplazamiento], hex, cont, desplazamiento);
	if(size==-1) printf("error de escritura\n");
	else printf("escritos %lld bytes de %s en %p\n", size, Arg[2+desplazamiento], hex);
}

ssize_t EscribirFichero (char *f, void *p, size_t cont, int overwrite){
	ssize_t  n;
	int df,aux, flags=O_CREAT | O_EXCL | O_WRONLY;

	if (overwrite)
		flags=O_CREAT | O_WRONLY | O_TRUNC;

	if ((df=open(f,flags,0777))==-1)
		return -1;

	n=write(df,p,cont);
	if (n==-1){
		aux=errno;
		close(df);
		errno=aux;
		return -1;
	}
	close (df);
	return n;
}


//MEMDUMP
void memdump(char* Arg[], int numA, tListM LM){
	if(numA<3){
		printf("faltan argumentos\n");
		return;
	}

	void* hex;
	if(*Arg[1]=='0' && *(Arg[1]+1)=='x') hex= (int*)strtol(Arg[1]+2, NULL, 16);
	else hex= (int*)strtol(Arg[1], NULL, 16);

	size_t cont= (size_t)strtoul(Arg[2],NULL,10);

	tPosLM p= findHex(hex, LM);
	tNodeMem d;
	if(p!=NULL){
		d=getDataM(p, LM);
		if(cont<=0){
			printf("lectura de %s bytes no permitida\n", Arg[2]);
			return;
		}
		if(d.space<cont){
			printf("aceso fuera de rango en %p\n", hex);
			return;
		}

		printf("Volcando %s bytes desde la direccion %p\n", Arg[2], hex);
		for(int i=0; i<cont; i++){
			printf("%c  ", *(char*)(hex+i));
		}printf("\n");
		for(int i=0; i<cont; i++){
			printf("%02X ", *(char*)(hex+i));
		}printf("\n");
	}
}


//MEMFILL
void memfill(char* Arg[], int numA, tListM LM){
	if(numA<4){
		printf("faltan argumentos\n");
		return;
	}

	void* hex;
	if(*Arg[1]=='0' && *(Arg[1]+1)=='x') hex= (int*)strtol(Arg[1]+2, NULL, 16);
	else hex= (int*)strtol(Arg[1], NULL, 16);

	size_t cont= (size_t)strtoul(Arg[2],NULL,10);

	tPosLM p= findHex(hex, LM);
	tNodeMem d;
	if(p!=NULL){
		d=getDataM(p, LM);
		if(cont<=0){
			printf("escritura de %s bytes no permitida\n", Arg[2]);
			return;
		}
		if(d.space<cont){
			printf("aceso fuera de rango en %p\n", hex);
			return;
		}
		LlenarMemoria(hex, cont, (unsigned char)*Arg[3]);
		printf("Llenando %d bytes de memoria con el byte (%02X) a partir de la direccion %p\n", cont, (unsigned char)*Arg[3], hex);
	}	
}

void LlenarMemoria (void *p, size_t cont, unsigned char byte){
	unsigned char *arr=(unsigned char *) p;
	size_t i;

	for (i=0; i<cont;i++) arr[i]=byte;
}


//MEMORY
void memory(char* Arg[], int numA, tListM LM){
	bool blocks=0, funcs=0, vars=0, pmap=0;
	int static static1 = 1, static2 = 2, static3 = 3;
	if(numA==2){
		if(strcmp(Arg[1], "-all")==0){
			blocks=1, funcs=1, vars=1;
		}else if(strcmp(Arg[1], "-blocks")==0){
			blocks=1;
		}else if(strcmp(Arg[1], "-funcs")==0){
			funcs=1;
		}else if(strcmp(Arg[1], "-vars")==0){
			vars=1;
		}else if(strcmp(Arg[1], "-pmap")==0){
			pmap=1;
		}else printf("Parámetro no válido");

		if(vars){
			printf("Variables locales\t %p,\t %p,\t %p \n", &blocks, &funcs, &vars);
        	printf("Variables globales\t %p,\t %p,\t %p \n", &g1, &g2, &g3);
        	printf("Variables estaticas\t %p,\t %p,\t %p \n", &static1, &static2, &static3);
		}
		if(funcs){
			printf("Funciones programa\t %p,\t %p,\t %p \n", memory, memfill, allocate);
			printf("Funciones librería\t %p,\t %p,\t %p \n", printf, time, strtoul);
		}
		if(blocks){
			printf("******Lista de bloques asignados para el proceso %d\n", getpid());
			printType(NULL, LM);
		}
		if(pmap) Do_pmap();

	}else printf("Parámetro no válido\n");
}

void Do_pmap (void){
	pid_t pid;       /*hace el pmap (o equivalente) del proceso actual*/
	char elpid[32];
	char *argv[4]={"pmap",elpid,NULL};

	sprintf (elpid,"%d", (int) getpid());
	if ((pid=fork())==-1){
		perror ("Imposible crear proceso");
		return;
		}
	if (pid==0){
		if (execvp(argv[0],argv)==-1)
			perror("cannot execute pmap (linux, solaris)");
			
		argv[0]="procstat"; argv[1]="vm"; argv[2]=elpid; argv[3]=NULL;   
		if (execvp(argv[0],argv)==-1)/*No hay pmap, probamos procstat FreeBSD */
			perror("cannot execute procstat (FreeBSD)");
			
		argv[0]="procmap",argv[1]=elpid;argv[2]=NULL;    
				if (execvp(argv[0],argv)==-1)  /*probamos procmap OpenBSD*/
			perror("cannot execute procmap (OpenBSD)");
			
		argv[0]="vmmap"; argv[1]="-interleave"; argv[2]=elpid;argv[3]=NULL;
		if (execvp(argv[0],argv)==-1) /*probamos vmmap Mac-OS*/
			perror("cannot execute vmmap (Mac-OS)");      
		exit(1);
	}
	waitpid (pid,NULL,0);
}

//RECURSIVA
void recurse(char* Arg[], int numA){
	if(numA<2){
		return;
	}
	int n= (int)strtoul(Arg[1], 0, 10);
	Recursiva(n);
}
void Recursiva (int n){
  char automatico[TAMANO];
  static char estatico[TAMANO];

  printf ("parametro:%3d(%p) array %p, arr estatico %p\n",n,&n,automatico, estatico);

  if (n>0)
    Recursiva(n-1);
}