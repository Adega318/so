#include "comandP2.h"
#include "listMem.h"

struct modComMem ModComMemCreate(){
	struct modComMem modArg;
	modArg.malloc=0, modArg.createShared=0, modArg.shared=0, modArg.mmap=0, modArg.delKey=0, modArg.addr=0;
	modArg.read=0, modArg.o=0, modArg.blocks=0, modArg.funcs=0, modArg.vars=0, modArg.all=0;
	modArg.pmap=0;
	return modArg;
}

void allocate(char* Arg[], int numA, tListM *bloquesMem){
	struct modComMem modArg=ModComMemCreate();
	bool standard=1;
	bool standardPlus=0;

	if(numA>1 && *Arg[1]=='-')
	{
		standard=0;
		if(strcmp(Arg[1], "-malloc")==0) modArg.malloc=1;
		else if(strcmp(Arg[1], "-createshared")==0) modArg.createShared=1;
		else if(strcmp(Arg[1], "-shared")==0) modArg.shared=1;
		else if(strcmp(Arg[1], "-mmap")==0) modArg.malloc=1;
		else{ standard=1;}
	}

	if(modArg.malloc) standardPlus=allocateMalloc(Arg, numA, bloquesMem);
	else if(modArg.shared) standardPlus=allocateShared(Arg, numA, bloquesMem);
	else if(modArg.createShared) standardPlus=allocateCreateshared(Arg, numA, bloquesMem);

	if(standard){
		printf("******Lista de bloques asignados ");
		if(standardPlus) printf("%s ", Arg[1]);
		printf("para el proceso %d\n", getpid());
		printType(standardPlus?Arg[1]:NULL, bloquesMem);
	}
}

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

bool allocateShared(char* Arg[], int numA, tListM* bloquesMem){
	if(numA==2 || (numA>2 && *Arg[2]=='-')) return 1;
	else{
		tNodeMem data;
		int id;
		key_t key= (key_t)strtoul(Arg[2],NULL,10);

		if(id=ObtenerMemoriaShmget(key, 0, &data)==NULL)printf("No se asignan bloques de 0 bytes\n");
		else if ((data.hex=shmat(id,NULL,0))==(void*) -1){
			perror("error1");
		}else{
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
		if ((hex=ObtenerMemoriaShmget(cl,size, &data)!=NULL)){
			insertDataM(data, bloquesMem);
			printf ("Asignados %lu bytes en %p\n",(unsigned long) size, data.hex);
		}
		else printf ("Imposible asignar memoria compartida clave %lu:%s\n",(unsigned long) cl,strerror(errno));
	}return 0;
}

void * ObtenerMemoriaShmget (key_t clave, size_t tam, tNodeMem* Mnode){
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