#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <wchar.h>
struct test{
	void (*test)();
	int i;
};

void test()
{
	printf("this is a test\n");
}

const char* get_name()
{
	return "TCP";
}
/*
typedef struct{
	int counter;
}atomic_t;

static inline void atomic_inc(atomic_t *v) 
{
	asm volatile("LOCK incl %0"
			: "+m" (v->counter)
			);
}

static inline void atomic_dec(atomic_t *v)
{                                         
	asm volatile("LOCK decl %0"
			: "+m" (v->counter));
}
*/

unsigned long InterlockedIncrement(unsigned long lpAddend)
{/*
	atomic_t v;
	v.counter = lpAddend;
	atomic_inc(&v);*/
	__sync_fetch_and_add(&lpAddend, 1);
}

int main()
{
	struct test t;
	t.test = test;
	t.test();
	unsigned long i = (unsigned long)-1;
	printf("%s\n", get_name());
	printf("%d\n", i);
	wprintf(L"%S\n", L"wchar test");
	const char * file = "this is\n";
	printf("%c\n", file[3]);
	i = 6;
	__sync_fetch_and_add(&i, 1);
	int j = 0;
	j = __sync_bool_compare_and_swap(&j, 0, 0);
	printf("j = %d\n", j);
	//InterlockedIncrement(i);
	printf("%d\n", i);
	char buf[256] = {0};
	printf("buf item count: %d\n", _countof(buf));
	return 0;
}
