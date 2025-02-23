#include <stdio.h>

int main(void) {
	//unsigned long int var;
	//char var;
	//unsigned char var;
	unsigned short var;
	//int var;
	//char  *ptr = &var;
	//unsigned char  *ptr = &var;
	unsigned short  *ptr = &var;
	//unsigned long int *ptr = &var;
	unsigned long int addr = 0;
	unsigned long int addr1 = 0;

	addr = (unsigned long int)ptr;
	ptr++;
	addr1 = (unsigned long int)ptr;
	printf("size is addr=0x%lx addr2=0x%lx  %lx\n", addr, addr1, addr1 - addr);
}
