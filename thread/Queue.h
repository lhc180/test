#ifndef Queue_H
#define Queue_H

typedef char Item;
typedef struct node * PNode;
typedef struct node
{
	Item data;
	PNode next;
}Node;

typedef struct
{
	PNode front;
	PNode rear;
	int size;
}Queue;

//init queue and set null
Queue *InitQueue();

//destroy queue
void DestroyQueue(Queue *pqueue);

void ClearQueue(Queue *pqueue);

int IsEmpty(Queue *pqueue);

int GetSize(Queue *pqueue);

//return head element
PNode GetFront(Queue *pqueue,Item *pitem);

//return tail element
PNode GetRear(Queue *pqueue,Item *pitem);

//In queue
PNode EnQueue(Queue *pqueue,Item item);

//out queue
PNode DeQueue(Queue *pqueue,Item *pitem);

//traverse queue and call visit func
void QueueTraverse(Queue *pqueue,void (*visit)(Item));

#endif
