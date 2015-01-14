#include "Queue.h"
#include <stdio.h>
#include <glib-2.0/glib.h>

void print(Item i)
{
	printf("the node element is: %c\n",i);
}

void* task(Queue* pq)
{
	printf("\nThread task: traverse queue from head to tail each elements are:\n");	
	QueueTraverse(pq,print);
}

int main()
{
	Queue *pq = InitQueue();
	int		i;
	char	item;
	char	ch;
	GThread *	gthread;

	
	printf("push 10 elements into queue in order\n");

	for(i = 0; i < 10; i++)
	{
		ch = getchar();
		EnQueue(pq, ch);
		GetRear(pq, &item);
		printf("%c\t", item);
	}
	printf("\n");
	gthread = g_thread_new("QueueTraverse", (GThreadFunc)task, (gpointer)pq);
	sleep(1);
	printf("elements pull off queue in order\n");

	for(i = 0; i < 10; i++)
	{
		DeQueue(pq, &item);
		printf("%c\t", item);
	}
	printf("\n");

//	g_thread_join(gthread);
	ClearQueue(pq);
	if(IsEmpty(pq))
		printf("\nset queue null success\n");
	DestroyQueue(pq);
	printf("queue is destroyed\n");
}
