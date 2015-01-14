#include <stdio.h>
#include "list.h"

typedef struct Node	Node;
struct	Node{
	struct list_head	*list;
	char				*text;
	int					num;
}

int main()
{
	Node	node;
	struct list_head	*list;
	struct list_head	*;
	INIT_LIST_HEAD(node->list);
	list_for_each_entry_safe(){
	
	}
	node	=	list_entry(list, Node, list);

}
