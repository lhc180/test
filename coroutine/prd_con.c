#include <stdlib.h>
#include <stdio.h>
#include <ucontext.h>

int product = 0;
ucontext_t main_context, producter_context, consumer_context;

void producter(void)
{
	printf("start producter, and do initialization!\n");
	swapcontext(&producter_context, &main_context);
	while(1)
	{
		product = 1;
		sleep(1);
		printf("put a product\n");
		swapcontext(&producter_context, &consumer_context);
	}
}

void consumer(void)
{
	printf("start consumer, and do initilazation!\n");
	swapcontext(&consumer_context, &main_context);
	while(1)
	{
		product = 0;
		sleep(1);
		printf("get a product!\n");
		swapcontext(&consumer_context, &producter_context);
	}
}

void init_context(void)
{
	char producter_stack[SIGSTKSZ];
	char consumer_stack[SIGSTKSZ];
	printf("SIGSTKSZ %d\n", SIGSTKSZ);

	printf("init1\n");
	getcontext(&producter_context);
	producter_context.uc_link			=	&main_context;
	producter_context.uc_stack.ss_sp	=	producter_stack;
	producter_context.uc_stack.ss_size	=	sizeof(producter_stack);
	makecontext(&producter_context, (void(*)(void))producter, 0);

	printf("init2\n");
	getcontext(&consumer_context);
	consumer_context.uc_link			=	&main_context;
	consumer_context.uc_stack.ss_sp	=	consumer_stack;
	consumer_context.uc_stack.ss_size	=	sizeof(consumer_stack);
	makecontext(&consumer_context, (void(*)(void))consumer, 0);
	return;
}

int main()
{
	static int is_finishd = 0;
	init_context();
	if(!is_finishd)
	{
		is_finishd = 1;
		while(1)
		{
			printf("main1\n");
			swapcontext(&main_context, &producter_context);
			printf("main2\n");
			swapcontext(&main_context, &consumer_context);
			printf("main3\n");
		}
	}
	return 0;
}
