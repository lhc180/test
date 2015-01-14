#include <stdio.h>
#include <uuid/uuid.h>

typedef struct _GUID
{
	unsigned long Data1;
	unsigned short Data2;
	unsigned short Data3;
	unsigned char Data4[8];
} GUID;

int main()
{
	uuid_t uu;
	int i;
	uuid_generate(uu);
	for(i = 0; i < 16; i++){
		printf("%02x-", uu[i]);
	}
	printf("\n");
	printf("sizeof(uu):%d\n", sizeof(uu));
	printf("sizeof(GUID)%d\n", sizeof(GUID));
	
	return 0;
}
