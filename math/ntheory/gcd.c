#include<stdio.h>
#include<stdlib.h>

int m_gcd(int var1, int var2){

	int q = 0;
	int p = 0;
	int r = 0;

	if (var1 > var2){
		p = var1;
		q = var2;
 	} else {
		p = var2;
		q = var1;
	}
	while(q != 0) {
		r = p % q;
		p = q;
		q = r;
	}
	return p;
}

int main()
{
	int var1 = 128, var2 = 1024;

	printf("gcd for var1=%d var2=%d is %d\n",var1, var2,m_gcd(var1, var2));
}
