#ifndef __OURHDR_H
#define __OURHDR_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define DEBUG 1
#ifdef DEBUG
#define LIDE printf
#else
#define LIDE(fmt...)
#endif
#endif
