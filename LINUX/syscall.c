#include <syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main()
{
	long ID1, ID2;
	ID1	=	syscall(SYS_getpid);
	printf("syscall(SYS_getpid) = %ld\n", ID1);
	ID2 = getpid();
	printf("getpid() = %ld\n", ID2);
	return 0;
}
