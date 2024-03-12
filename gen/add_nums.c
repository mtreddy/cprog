#include<stdio.h>
#include<stdlib.h>


int main(int argc, char **argv)
{
	if(argc < 3){
		printf("Help: add <into> <int>\n");
		return 0;
	}
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	int carry = 0;
	printf("\n a=0x%x b=0x%x\n", a ,b);
	while(b != 0) {
		printf("a=%x b=%x\n", a, b);
		carry =  a&b;
		a = a^b;
		b = carry << 1;
	}
	printf("sum=%x\n", a);
}
