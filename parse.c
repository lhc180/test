#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>

int main(int argc, char **argv) {
    DIR *dirp;
    struct dirent *direntp;
    int stats;
    char buf[80];
    if (argc != 2) {
        printf("Usage %s filename\n\a", argv[0]);
        exit(1);
    }
    if ((stats == -1))exit(1);
    if ((dirp = opendir(argv[1])) == NULL) {
        printf("Open Directory %s Error%s\n",
                argv[1], strerror(errno));
        exit(1);
    }
    while ((direntp = readdir(dirp)) != NULL){
        sprintf(buf,"%s", direntp->d_name);
		printf("%s\n", buf);
    }
    closedir(dirp);
    exit(1);
}
        
