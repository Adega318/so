#include "comandP1.h"

struct modCom ModComCreate(){
	struct modCom modArg;
	modArg.reca=0, modArg.recb=0, modArg.hid=0, modArg.lon=0, modArg.link=0, modArg.acc=0;
	return modArg;
}

struct modCom ModComSet(struct modCom modArg){
	modArg.reca=0, modArg.recb=0, modArg.hid=0, modArg.lon=0, modArg.link=0, modArg.acc=0;
	return modArg;
}

void create(char* Arg[], int numA){
	int i=1;
	bool file=0;
	char p[PATH_MAX];
	FILE *filePath;

	while (numA>1 && i<numA && *Arg[i]=='-'){
		if(strcmp(Arg[i], "-f")==0) file=1;
        else return;
		i++;
	}

	if(i<numA){
		if(!file && mkdir(Arg[i], S_IRWXU)==-1){
			if(errno==EEXIST)perror("Imposible crear");
			else perror("error");
		}
		if(file){
			filePath=fopen(Arg[i], "w+");
			if(filePath==NULL){
				if(errno==EEXIST)perror("Imposible crear");
				else perror("error");
			}
			else fclose(filePath);
		}
		
	}else if(getcwd(p, sizeof(p))==NULL) {perror("error");}else printf("%s\n",p);
}

void statfun(char* Arg[], int numA){
	int i=1;
	struct modCom modArg=ModComCreate();
	struct stat stats;
	char p[PATH_MAX];
	
	while (numA>1 && i<numA && *Arg[i]=='-')
	{
		if(strcmp(Arg[i], "-long")==0) modArg.lon=1;
        else if(strcmp(Arg[i], "-link")==0) modArg.link=1;
        else if(strcmp(Arg[i], "-acc")==0) modArg.acc=1;
		else printf("error: %s no es un modificador valido\n", Arg[i]);
		i++;
	}
	
	if(i<numA){
		for(i=i; i<numA; i++){
			if (lstat(Arg[i], &stats)==0){
				statprint(modArg, Arg[i], Arg[i], stats);
			}else perror("error");
		}
	}else if(getcwd(p,sizeof(p))==NULL) {perror("error");}else printf("%s\n",p);
}

//subfunción de statfun
void statprint (struct modCom modArg, char* pArg,char* Arg, struct stat stats){
	char* salida;
	int size=0;
	if(modArg.lon){
		struct tm *time;
		if(modArg.acc)time=gmtime(&stats.st_atim.tv_sec);
		else time=gmtime(&stats.st_mtim.tv_sec);
		printf("%d/%02d/%02d-%02d:%02d ", time->tm_year+1900, time->tm_mon+1, time->tm_mday, time->tm_hour+2, time->tm_min);
		printf("%3d ", (int)stats.st_nlink);
		printf("(%8d)\t", (int)stats.st_ino);
		printf("%s\t%s ", getpwuid(stats.st_uid)->pw_name, getgrgid(stats.st_gid)->gr_name);
		printf("%s ", ConvierteModo(stats.st_mode));
	}
	printf("%8d ", (int)stats.st_size);
	printf("%s", pArg);
	if(modArg.link && LetraTF(stats.st_mode)=='l'){
		salida=malloc(PATH_MAX);
		size= (int)readlink(Arg, salida, PATH_MAX);
		if (size>=0){
			printf(" --> %.*s",size, salida);
		}else perror("error");
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
	struct modCom modArg=ModComCreate();
	char p[PATH_MAX];

	while (numA>1 && i<numA && *Arg[i]=='-'){
		if(strcmp(Arg[i], "-reca")==0) modArg.reca=1;
		else if(strcmp(Arg[i], "-recb")==0) modArg.recb=1;
		else if(strcmp(Arg[i], "-hid")==0) modArg.hid=1;
		else if(strcmp(Arg[i], "-long")==0) modArg.lon=1;
        else if(strcmp(Arg[i], "-link")==0) modArg.link=1;
        else if(strcmp(Arg[i], "-acc")==0) modArg.acc=1;
		else printf("error: %s no es un modificador valido\n", Arg[i]);
		i++;
	}
	if(modArg.reca && modArg.recb) modArg.reca=0;

	if(i<numA) for(i=i; i<numA; i++) listrec(Arg[i], modArg);
	else if(getcwd(p, sizeof(p))==NULL) {perror("error");}else printf("%s\n",p);
}

//subfunción de list
void listrec(char* Arg, struct modCom modArg){
	DIR* dp;
	struct dirent *dirp;
	struct stat stats;
	char* concat= malloc(PATH_MAX);
	char format;
	struct modCom modArg2=modArg;

	if(!modArg.reca && !modArg.recb) printf("************%s\n", Arg);
	dp=opendir(Arg);
	if(dp==NULL)perror("error");
	else{
		if (modArg.reca){
			modArg2.reca=0;
			listrec(Arg, modArg2);
		}

		while ((dirp=readdir(dp))!=NULL){
			if((strcmp(dirp->d_name, ".")!=0 && strcmp(dirp->d_name, "..")!=0) || modArg.hid){
				strcpy(concat, Arg);
				if(strcmp(Arg, "/")!=0) strcat(concat, "/");
				strcat(concat, dirp->d_name);
				
				if (lstat(concat, &stats)==0){
					format=LetraTF(stats.st_mode);

					if(!(modArg.reca || modArg.recb)) statprint(modArg, dirp->d_name, concat, stats);
					else if(format=='d' && strcmp(dirp->d_name, ".")!=0 && strcmp(dirp->d_name, "..")!=0) listrec(concat, modArg);

				}else perror("error");
			}
		}if(closedir(dp)==-1) perror("error");

		if (modArg.recb){
			modArg2.recb=0;
			listrec(Arg, modArg2);
		}
	}
	free(concat);
}
//

void delete(char *Arg[], int numA){
	bool aux;
    struct stat stats;
    char p[PATH_MAX];
    DIR *dir;
    struct dirent *dirname;
	
	if(numA>1) for(int i=1; i<numA; i++){

		aux=1;
		if(lstat(Arg[i], &stats) == -1) perror("error");
		else{
			if(LetraTF(stats.st_mode)=='d'){
        		if((dir = opendir(Arg[i])) == NULL) perror("error");
				else{
					while((dirname = readdir(dir)) != NULL) {
            			if(strcmp(dirname->d_name, ".") != 0 && strcmp(dirname->d_name, "..") != 0) aux=0;
					}if(closedir(dir)==-1) perror("error");
					if(aux && rmdir(Arg[i]) == -1) perror("error");
        		}
			}else if(remove(Arg[i])==-1)perror("error");
			
    	}

	}else if(getcwd(p, sizeof(p))==NULL) {perror("error");}else printf("%s\n",p);
}

void deltree(char *Arg[], int numA){
    struct stat stats;
    char p[PATH_MAX];
    DIR *dir;
    struct dirent *dirname;
	char* recpath[2];

	if(numA>1) for(int i=1; i<numA; i++){
		if(lstat(Arg[i], &stats)==-1)perror("error");
		else{
			if(LetraTF(stats.st_mode)=='d'){
				if((dir = opendir(Arg[i])) == NULL) perror("error");
				else{
					recpath[1]= malloc(PATH_MAX);
					while((dirname = readdir(dir)) != NULL) {
            			if(strcmp(dirname->d_name, ".") != 0 && strcmp(dirname->d_name, "..") != 0){
							strcpy(recpath[1], Arg[i]);
							if(strcmp(Arg[i], "/")!=0) strcat(recpath[1], "/");
							strcat(recpath[1], dirname->d_name);
							deltree(recpath, 2);
						}
					}if(closedir(dir)==-1) perror("error");
					if(rmdir(Arg[i]) == -1) perror("error");
					free(recpath[1]);
        		}
			}else if(remove(Arg[i])==-1)perror("error");
		}
	}else if(getcwd(p, sizeof(p))==NULL) {perror("error");}else printf("%s\n",p);
}