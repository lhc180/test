#include "ourhdr.h"

int main()
{
	pid_t pid;

	printf("\nprocess start\n");

	pid = fork();
	if(pid == 0){
		printf("child pid: %d\n", getpid());
	}
	else if(pid > 0)
		printf("father pid: %d,child has pid: %d\n", getpid(), pid);
	else
		printf("Fork error\n");
	printf("processs work,pid: %d\n\n", pid);
	return 	0;
}
