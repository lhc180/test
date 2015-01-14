#include <stdio.h>

int main()
{
	int		i = 0x12345678;
	union test{
		char	ch;
		int		data;
	};
	union test	test;
	test.data = i;
	printf("ch: 0x%x\n", test.ch);
	return 0;
}
