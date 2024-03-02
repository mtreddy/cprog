/*
 * Program to get leading zeros in give integer
 */
#include<stdio.h>

typedef unsigned int uint32_t;
int main(){
	uint32_t x = 0x000FFFFF;
	int cnt = 0;
	if(x < 0x0000FFFF) {
		x = x << 16;
		cnt = cnt + 16;
	}
	if(x < 0x00FFFFFF) {
		x = x << 8;
		cnt = cnt + 8;
	}
	if(x < 0x0FFFFFFF)  {
		x = x << 4;
		cnt = cnt + 4;
	}
	if(x < 0x3FFFFFFF) {
		x = x << 2;
		cnt = cnt + 2;
	}
	if(x < 0x7FFFFFFF) {
		x = x << 1;
		cnt = cnt + 1;
	}
	printf("leading zeros %d\n",cnt);
}
