#include <stdio.h>

#define DEBUG 0
#ifdef	DEBUG
#define lide_printf printf
#else
#define lide_printf(fmt...)
#endif
