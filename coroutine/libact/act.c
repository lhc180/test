#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <ucontext.h>
#include "act.h"

#define act_access_proc_begin() do{\
	pthread_mutex_lock(&act_procs_mutex);\
}while(0)

#define act_access_proc_end() do{\
	pthread_mutex_unlock(&act_procs_mutex);\
}while(0)

static pthread_mutex_t act_procs_mutex = PTHREAD_MUTEX_INITIALLIZER;

typedef struct act_proc act_proc_t;

struct act_porc{
	act_pid		pid;
	ucontext_t	*ctx;
	act_status	status;

	act_proc_t	*prev;
	act_proc_t	*next;
};

static act_pid	act_max_pid;
static act_proc_t* act_procs;

typedef struct act_sche act_sche_t;

struct act_sche{
	pthread_t	tid;
	ucontext_t	*ctx;
	act_proc_t	*running_proc;
};

static int act_sche_num;
static act_sche_t **acr_sches;

static void *act_scheduler(void* data)
{
	
}

