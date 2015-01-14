#include <stdio.h>

long simple_loop(long x)
{
	long i, ret_val = 0;
#pragma novector
	for(i = 0; i < x; i++){
		ret_val += i;
	}
	return ret_val;
}
int main()
{

}
