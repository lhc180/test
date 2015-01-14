#include <stdio.h>

int main()
{
	unsigned int x = 2;
	unsigned int y = 2;
	unsigned long z;

	z = x<<16;
	printf("x = %u, z = %lx\n", x, z);
	z <<= 16;
	z |= y;
	printf("x = %u, z = %lx\n", x, z);

	printf("sizeof(unsigned int): %d\n", sizeof(unsigned int));
	printf("sizeof(unsigned long): %d\n", sizeof(unsigned long));

	return 0;
}

