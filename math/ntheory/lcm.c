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
int lcm(int a, int b) {
	return abs(a*b)/m_gcd(a,b);
}
int main(){
	int a = 8, b =16;
	printf("lcdm of %d and %d is %d\n", a, b, lcm(8,16));
}
