#include <stdio.h>
#include <setjmp.h>

int main()
{
	jmp_buf evn;
	static int count = 0;
	if(setjmp(evn) == 0)
	{
		printf("evn start\n");
		longjmp(evn, 0);
	}

	if(setjmp(evn) == 0)
	{
		printf("jmp 2\n");
		longjmp(evn, 0);
	}
	
	if(count == 0){
		printf("count %d\n", count++);
		longjmp(evn, 2);
	}

	printf("the end\n");
	return 0;
}
