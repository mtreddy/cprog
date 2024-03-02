/*
 * This program returns number of bits set in given variable
 * gcc -o count_bits count_bits.c
 */
#include<stdio.h>
typedef unsigned int uint32_t;
int  get_bits_in_sparse(uint32_t x) {
	int  cnt = 0;
	while(x != 0) {
		x = x & (x-1);
		cnt++;
	}
	return cnt;
}
uint32_t no_of_set_bits(uint32_t val)
{
	val = (val & 0x55555555) + ((val >> 1 ) & 0x55555555);
	val = (val & 0x33333333) + ((val >> 2 ) & 0x33333333);
	val = (val & 0x0F0F0F0F) + ((val >> 4 ) & 0x0F0F0F0F);
	val = (val & 0x00FF00FF) + ((val >> 8 ) & 0x00FF00FF);
	val = (val & 0x0000FFFF) + ((val >> 16 ) & 0x0000FFFF);
	printf("nu of bits in val=0x%x \n",val);
	return val;
}
int main() {
	unsigned int  val = 0xFFFF;
	printf("bits st %d\n",no_of_set_bits(val));
	printf("bits st %d\n",get_bits_in_sparse(0x8421));

}

