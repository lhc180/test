#include <stdio.h>
#include <sys/time.h>

static int lide = 0; 
//#define DEBUG 0
#ifdef DEBUG
#define IN  {printf("\n%d   %s>>>>>>>>>>>>>>>>\n",lide++, __func__}
#define OUT {printf("%d %s<<<<<<<<<<<<<<<<\n", lide, __func__}
#else
#define IN    {};
#define OUT    {};
#endif

#define TIME    1
	struct timeval start;
	struct timeval end;
#ifdef TIME
void inline db_time_start(struct timeval *start)
{
	gettimeofday(start, NULL);
}
void inline db_time_end(char *ch, struct timeval *time)
{
	struct timeval end;
	gettimeofday(&end, NULL);
	printf("%s\ttime: %2ds %6d\n", ch, (int)((end.tv_sec-time->tv_sec)), (int)(end.tv_usec-time->tv_usec));
}
#else
void inline db_time_start(struct timeval *start){};
void inline db_time_end(char *ch, struct timeval *time){}
#endif

int main() {
	db_time_start(&start);
	sleep(1);
	db_time_end(NULL, &start);
	return 0;
}

