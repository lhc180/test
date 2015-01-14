#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "ourhdr.h"

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

#define BUFFSIZE 8192
int main()
{
	int n;
	char buf[BUFFSIZE];
	while((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
		if(write(STDOUT_FILENO, buf, n) != n)
			perror("write error");
	if(n < 0)
		perror("read error");
	/*
	int fd;
	if(fd = open("./file.hole",O_RDWR|O_CREAT, 644) == -1)
		perror("open filed");
	if(write(fd, buf1, 10) != 10)
		perror("buf1 write error");
	//offset now is 10
//	if(lseek(fd, 40, SEEK_SET) == -1)
//		error("lseek error");
	//offset now is 40
//	if(write(fd, buf2, 10) != 10)
//		error("buf2 write error");
	close(fd);
	*/
	return 0;
}
