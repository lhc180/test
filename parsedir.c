#include <stdio.h> 
#include <stdlib.h>    
#include "limits.h"
#include <string.h>  
#include <dirent.h> 
#include <dlfcn.h>

#define MAX_LEN 256


typedef void* (*test)();
int main(void) 
{ 
    DIR *dir; 
    struct dirent *ptr; 
    static char flow[MAX_LEN];
    int num = 0, i = 0;
   
	const char buf[256] = "test";

	char path[256] = {0};
	//getcwd(path, 256);
	int rslt = readlink("/proc/self/exe", path, PATH_MAX);
	if (rslt < 0 || rslt >= PATH_MAX)
	{   
		return -1;
	} 

	path[rslt] = '\0';
	for (i = rslt; i >= 0; i--)
	{
		if (path[i] == '/')
		{
			path[i+1] = '\0';
			break;
		}
	}

    if ((dir=opendir(path)) == NULL) 
    { 
        perror("Open dir error..."); 
        exit(1);        
    } 
    // readdir() return next enter point of directory dir
	
	void * handle;
	test test;
    while ((ptr=readdir(dir)) != NULL) 
	{
		strcpy(flow, ptr->d_name);
		for(i = 0; i < MAX_LEN; i++)
		{
			if(flow[i]=='.' && flow[i+1]=='s' && flow[i+2]=='o'){
				printf("%s\n", flow);
				strcat(path, flow);
				printf("%s\n", path);
				handle = dlopen(path, RTLD_LAZY/*|RTLD_GLOBAL*/);
				test= dlsym(handle, buf);
			}
		}
	} 
    closedir(dir); 
	test();
}
