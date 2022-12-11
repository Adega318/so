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

char * Ejecutable (char *s){
	char path[MAXNAME];
	static char aux2[MAXNAME];
	struct stat st;
	char *p;

	if (s==NULL || (p=getenv("PATH"))==NULL) return s;

	if (s[0]=='/' || !strncmp (s,"./",2) || !strncmp (s,"../",3)) return s;       //is an absolute pathname

	strncpy (path, p, MAXNAME);
	for (p=strtok(path,":"); p!=NULL; p=strtok(NULL,":")){
       sprintf (aux2,"%s/%s",p,s);
	   if (lstat(aux2,&st)!=-1) return aux2;
	}
	return s;
}

int OurExecvpe(const char *file, char *const argv[], char *const envp[]){
    return (execve(Ejecutable(file) ,argv, envp));
}

int main(){
    OurExecvpe("ls")
    return 0;
}


