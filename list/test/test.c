#include <stdio.h>
#include "list.h"

static inline DList* dlist_create(DList* list)
{
	list = (DList*)malloc(sizeof(DList));
	INIT_DLIST(list);
	return list;
}

int main()
{
	DList *list;
	list = dlist_create(list);
	list->data = (int*)malloc(1);
	*(int*)list->data = 8;
	printf("%d\n", *(int*)list->data);
	return 0;
}
