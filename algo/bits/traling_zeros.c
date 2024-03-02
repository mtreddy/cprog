/**
 * gcc -o ntz  trailing_zeros.c
 */
#include<stdio.h>
typedef unsigned int uint32_t;

int main() {

	uint32_t x = 0x12348C00;
	int cnt = 0;
	if((x & 0xFFFF) == 0) {x = x>>16; cnt += 16;}
	if((x & 0xFF) == 0)   {x = x>>8; cnt += 8;}
	if((x & 0xF) == 0) {x = x>>4; cnt += 4;}
	if((x & 0x3) == 0) {x = x>>2; cnt += 2;}
	if((x & 0x1) == 0) {x = x>>1; cnt += 1;}
	printf(" ntz=%d\n", cnt);
}
