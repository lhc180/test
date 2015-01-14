#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define PATH_MAX 1024
char * get_exe_path()
{
    static char buf[PATH_MAX];
    int i;
    int rslt = readlink("/proc/self/exe", buf, PATH_MAX);
    if (rslt < 0 || rslt >= PATH_MAX)
    {
        return NULL;
    }
    buf[rslt] = '\0';
    for (i = rslt; i >= 0; i--)
    {
        if (buf[i] == '/')
        {
            buf[i] = '\0';
            break;
        }
    }
	printf("%s\n", buf+i+1);
    return buf;
}

int main()
{
	char* path1 = (char*)malloc(256);
	char* path2 = (char*)malloc(256);
	char path[256] = {0};
	path1 = get_exe_path();
	//chdir("/home");
	path2 = getcwd(path, 256);
	printf("%s\n", path);
	printf("%s\n", path1);
	printf("%s\n", path2);

	DIR     *dir;
	if ((dir=opendir(path2)) == NULL)
	{   
		perror("Open dir error...");
		exit(1);
	}

	struct dirent *ptr;
	static char flow[256];
	int i = 0;

	while ((ptr=readdir(dir)) != NULL)
	{
		strcpy(flow, ptr->d_name);
		for(i = 0; i < 256; i++)
		{
			if(flow[i]== '.' && flow[i+1]== 's' && flow[i+2]=='o')
			{
				handle = dlopen(flow, RTLD_LAZY|RTLD_GLOBAL);
				Fn_GetInterface fn = (Fn_GetInterface)dlsym(handle, FunctionName);
				if ( !fn || !(piGet = fn()))
				{
					dlclose(handle);
					continue;
				}
			}
		}
	}

	return 0;
}
