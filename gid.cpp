#include <stdio.h>
#include <uuid/uuid.h>
#include <iostream>
void test()
{
	printf("this is a test\n");
}

void gid(const uuid_t &guid = {0})
{
	int i = 0;
	uuid_t id;
	uuid_copy(id, guid);
	for(i = 0; i < 16; i++)
		printf("-%2x", guid[i]);
	printf("\n");
}

int main()
{
	int i = 0;
	const uuid_t guid = {0xbe, 0xab};
	gid();
	gid(guid);
	//uuid_generate(guid);
	uuid_t id;
	printf("%2x\n", *guid);
	for(i = 0; i < 16; i++)
		printf("-%2x", guid[i]);
	printf("\n");
	uuid_copy(id, guid);
	for(i = 0; i < 16; i++)
		printf("-%2x", id[i]);
	printf("\n");

	return 0;
}
