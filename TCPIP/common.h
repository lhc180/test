#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 4567
#define LISTENQ 20
#define BUFFSIZE 4096*1024
#define FILE_NAME_MAX_SIZE 512
