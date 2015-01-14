#include <stdio.h>
#include <sys/time.h>

int main()
{
	int i = 0;
	struct timeval start, end;
	int *pi;
	int *pj;
	int tmp;
	//char	buf[8] = {'a', 'b', 'c', 'd', 'e', 'f'};
	char	buf[8] = {1, 2, 3, 4, 5, 6, 7};
	printf("buff addr: 0x%x\n", buf);
	printf("buf[0]: %d\n", buf[0]);
	char*	pb = &(buf[1]);
	printf("pb addr: 0x%x\n", pb);

	gettimeofday(&start, NULL);
	for(i = 0; i < 1024*1024; i++)
	{
		pi = (int*)buf;
		tmp = *pi;
	}
	gettimeofday(&end, NULL);
	timersub(&end, &start, &end);
	printf("1 time count: %d    :   %d\n", end.tv_sec, end.tv_usec);
	printf("pi addr: 0x%x\n", pi);
	printf("pi: %d\n", *pi);
	gettimeofday(&start, NULL);
	for(i = 0; i < 1024*1024; i++)
	{
		pj = (int*)pb;
		tmp = *pj;
	}
	gettimeofday(&end, NULL);
	timersub(&end, &start, &end);
	printf("2 time count: %d    :   %d\n", end.tv_sec, end.tv_usec);
	printf("pj addr: 0x%x\n", pj);
	printf("pj: %d\n", *pj);
	return 0;
}
