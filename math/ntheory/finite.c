#include<stdio.h>
#include<stdlib.h>

int gcd(int a, int b) {
	if (abs(b) > abs(a)) {
		gcd(b, a);
	}
		int r = 0;
	while(abs(b) > 0) {
		r = a%b;
		a = b;
		b = r;
		//printf("a=%d b=%d r = %d", a,b, r);
	}
	return a;
}


int main() {
	int a = 1547;
	int b = 560;
	printf("GCD for %d %d  is %d\n", a , b, gcd(a,b));
}

