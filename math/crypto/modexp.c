#include<stdio.h>
#include<malloc.h>
#include<math.h>


int *a;

int modexp(int base, int exp, int mod){
	int res = 0;
	int x = base;
	int i = 0;
	res = 1;
	if(base > exp)  {
		printf("Base > mod..\n");
	}
	while(exp!=0){
		if(a[i] != 0) 
			res = (x*res) % mod;
		x = (x*x) % (mod);
		printf("res=%d x=%d exp=%d\n", res, x, exp);
		exp = exp >> 1;
		i++;
	}
	printf("\n res=%d\n", res);

}

void find_dec2bin(int exp)
{
	int i = 0;
	int q = exp;
	int r = 0;
	
	while(q != 0){
		r = q%2;
		q = q/2;
		a[i++] = r;
		printf("\n%d", r);
	}
}
int main() {
	int base = 4;
	int exp = 13;
	int mod = 497;
	/*Fined len of array needed to stor bin*/
	int ind = 0;
	for(ind=0; pow(2,ind) < exp; ind++)
		printf("\n%d", ind);
	printf("Allocating size %d\n", ind);
    a = (int *)malloc(sizeof(int) * ind+1);
	find_dec2bin(exp);
	modexp(base, exp, mod);
}
