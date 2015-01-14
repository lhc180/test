#include "ourhdr.h"
#define DRAW(type) 		printf("ddsafs\n")
int main(void)
{
	DRAW(ds);
	printf("hello world from process ID %d\n", getpid());
	int a = 1;
	int b = 2;
	int c = 3;
	a = b = c;
	printf("a = %d, b = %d, c = %d\n", a, b, c);
	return 0;
}
