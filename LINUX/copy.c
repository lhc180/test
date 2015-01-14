#include "ourhdr.h"

int main()
{
	int c;
	while((c = getc(stdin)) != EOF)
		if (putc(c, stdout) == EOF)
			LIDE("output error\n");
	if(ferror(stdin))
		LIDE("input error");
	exit(0);
}
