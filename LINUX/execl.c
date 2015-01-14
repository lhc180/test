#include "ourhdr.h"

int main()
{
	printf("Executing ls\n");
	execl("/bin/ls", "ls", "-l", NULL);
	perror("execl failed to run ls");
	exit(1);
	return 0;
}
