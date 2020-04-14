#include<stdio.h>

int prng(int mod, int mul, int inc, int seed)
{
	int x = (mul*seed + inc)%mod; 
	return x;
}

int main(){
    int i = 0;
    int mod = 9;
	int mul = 7;
	int inc = 4;
	int seed = 3;
	for(i = 0; i < 10; i++) {
		seed = prng(mod , mul, inc, seed);
		printf("seed=%d\n", seed);
	}

}
