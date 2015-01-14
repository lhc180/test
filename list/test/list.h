#ifndef	__LIST_H
#define	__LIST_H

typedef	struct DList DList;
#define	INIT_DLIST(name)	{(name)->prev = (name);\
								(name)->next = (name);}

struct DList{
	DList	*prev;
	DList	*next;
	void	*data;
};

static inline void dlist_insert(DList *new, DList *list)
{
	list->next->prev	=	new;
	new->next	=	list->next;
	new->prev	=	list;
	list->next	=	new;
}

static inline void dlist_delete(DList *prev, DList *next)
{
	next->prev	=	prev;
	prev->next	=	next;
}

static inline void dlist_print(DList *list)
{
	printf("%p\n", list->data);
}

#endif
