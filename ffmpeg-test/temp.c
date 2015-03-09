#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE* fp = fopen("./temp.txt", "wb");

	if(NULL == fp)
	{
		perror("open file failed\n");
		exit(-1);
	}

	char buf[256] = {0};
	sprintf(buf,"This is a test\n");

	int i = 0;
	for(i = 0; i < 10; i++){
		fwrite(buf, sizeof(buf), 1, fp);
	}

	fclose(fp);

}
