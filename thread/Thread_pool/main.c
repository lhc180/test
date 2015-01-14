#include <stdio.h>
#include "threadpool.h"

void* work(void* arg)
{
    int *p = (int*) arg;
    printf("threadpool callback fuction : %d.\n", *p);
    sleep(1);
}

int main(void)
{
    struct threadpool *pool = threadpool_init(10, 20);
	int i = 0;
	while(1){
		threadpool_add_job(pool, work, (void*)&i);
		printf("%d\n", i);
		i++;
	}
    sleep(5);
    threadpool_destroy(pool);
    return 0;
}
