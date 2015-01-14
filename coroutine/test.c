#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define		crBegin		static int state = 0;switch(state){case 0:
#define		crReturn(x)	do{state=__LINE__;return x;case __LINE__:;}while(0)
#define		crFinish	}
int function(void)
{
	static int i = 0;
	crBegin;
	for(i; i < 10; i++) {
		crReturn(i);
	}
	crFinish;
}

int decompressor(void){
	static int c, len;
	crBegin;
	while(1){
		c = getchar();
		if(c == EOF)
			break;
		if(c == 0xFF){
			len = getchar();
			c = getchar();
			while(len--)
				crReturn(c);
		}else
			crReturn(c);
	}
	crReturn(EOF);
	crFinish;
}
void parser(int c){
	crBegin;
	while(1){
		if(c == EOF)
			break;
		if(isalpha(c)){
			do{
	//			add_to_token(c);
				printf("%c\n", c);
				crReturn();
			}while(isalpha(c));
	//		got_token(WORD);
		}
		printf("%c\n", c);
		//add_to_token();
		//got_token(PUNCT);
		crReturn();
	}
	crFinish;
}

int main()
{
	int i = 0;
	for(i = 0;i < 10; i++) {
		printf("%d\n",function());
	}
	while(1){
		parser(decompressor());
	}
	return 0;
}
