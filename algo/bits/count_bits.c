#include<stdio.h>


int main() {
	unsigned int  val = 0xFFFF;

	val = (val & 0x55555555) + ((val >> 1 ) & 0x55555555);
	val = (val & 0x33333333) + ((val >> 2 ) & 0x33333333);
	val = (val & 0x0F0F0F0F) + ((val >> 4 ) & 0x0F0F0F0F);
	val = (val & 0x00FF00FF) + ((val >> 8 ) & 0x00FF00FF);
	val = (val & 0x0000FFFF) + ((val >> 16 ) & 0x0000FFFF);
	printf("nu of bits in val=0x%x \n",val);
}

