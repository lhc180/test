#include <signal.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

static sigjmp_buf jmpbuf;

static void myfunc(int signo)
{
	printf("SIGQIUT\n");
	sleep(1);
	if(sigsetjmp(jmpbuf, 1) == 0){
		siglongjmp(jmpbuf, 2);
	}
	printf("siglongjmp\n");
}

int main()
{
	char *p = NULL;
	struct sigaction act;
	act.sa_handler = myfunc;
	act.sa_flags = SA_INTERRUPT;
	sigemptyset(&act.sa_mask);

	if(sigaction(SIGQUIT, &act, NULL) < 0)
		perror("sigaction");

	if(sigsetjmp(jmpbuf, 1) == 1)
	{
		printf("I am jmpted1\n");
	}else if(sigsetjmp(jmpbuf, 1) == 2){
		printf("I am jmpted2\n");
		siglongjmp(jmpbuf, 0);
	} else {
		printf("raise sig\n");
		raise(SIGQUIT);
	}
	printf("I am here\n");

	return 0;
}
