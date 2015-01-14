#include <stdio.h>
#include <math.h>

int main()
{
	float val = tan(78/100.0);
	printf("%f\n", val);

	printf("enverment: %s\n", getenv("PATH"));

	return 0;
}
