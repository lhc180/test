#ifndef H_DEBUG
#define H_DEBUG
#include <sys/time.h>

struct timeval lide_time;
void inline db_time_start(struct timeval *start)
{
    gettimeofday(start, NULL);
}
void inline db_time_end(char *ch, struct timeval *start)
{
    struct timeval end;
    gettimeofday(&end, NULL);
    timersub(&end, start, &end);
    printf("%s\ttime: %2ds %6d\n", ch, (int)(end.tv_sec), (int)(end.tv_usec));                                                                                              
}

static int lide = 0;  
#define DEBUG 0
#ifdef DEBUG
#define IN  {printf("\n%d %s>>>>>>>>>>>>>>>>\n",lide++, __func__);}
#define OUT {printf("%d %s<<<<<<<<<<<<<<<<\n", lide, __func__);}
#else
#define IN    {};
#define OUT    {};
#endif 

#endif