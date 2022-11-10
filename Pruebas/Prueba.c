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

int main(){
    void *hex= malloc(3);
    printf("%p", hex);

    return 0;
}

