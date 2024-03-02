/*
 * Program to reverse bits in given integer
gcc -o rev rev_bits.c
 */

#include<stdio.h>

int main() {
	unsigned int val = 0xe6a2c480, x=0;
  x = val;
  x = (x & 0x55555555) << 1 | (x & 0xAAAAAAAA) >> 1;
  x = (x & 0x33333333) << 2 | (x & 0xCCCCCCCC) >> 2;
  x = (x & 0x0F0F0F0F) << 4 | (x & 0xF0F0F0F0) >> 4;
  x = (x & 0x00FF00FF) << 8 | (x & 0xFF00FF00) >> 8;
  x = (x & 0x0000FFFF) << 16 | (x & 0xFFFF0000) >> 16;
  printf("x=0x%x val=0x%x\n",x, val);
}
