#include <stdio.h>  
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>  
void checkset();  

int main()  
{  
	sigset_t blockset;  
	sigemptyset(&blockset);  
	sigaddset(&blockset,SIGINT);  
	sigaddset(&blockset,SIGTSTP);  

	checkset();  

	sigprocmask(SIG_SETMASK,&blockset,NULL);  
	checkset();  

	sigaddset(&blockset,SIGTERM);  
	sigprocmask(SIG_BLOCK,&blockset,NULL);  
	checkset();  

	sigdelset(&blockset,SIGTERM);  
	sigprocmask(SIG_UNBLOCK,&blockset,NULL);  
	checkset();  

	return 0;
}  

void checkset()  
{  
	sigset_t set;  
	printf("checksetstart:\n");  

	if(sigprocmask(0,NULL,&set)<0)  
	{  
		printf("checksetsigprocmask error!!\n");  
		exit(0);  
	}  

	if(sigismember(&set,SIGINT))  
		printf("sigint\n");  
	if(sigismember(&set,SIGTSTP))  
		printf("sigtstp\n");  
	if(sigismember(&set,SIGTERM))  
		printf("sigterm\n");  
	printf("checksetend\n\n");  
}  
