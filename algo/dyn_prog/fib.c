#include<stdio.h>
int fn[25];
int len = 7;
int fib(int n)
{
	int i = 0;
	fn[0] = 0;
	fn[1] = 1;

	for(i=2; i <= n; i++){
		fn[i] = fn[i-1] + fn[i-2];
	}
    printf("%d %d\n", i-1, fn[i-1]);
	return fn[i-1];
}

int fib_r(int n) {
	if( n == 0)
		return 0;
	if(n == 1)
		return 1;

	return fib_r(n-1) + fib_r(n-2);

}
int fib_mem(int n) {
	if( n == 0)
		return 0;
	if(n == 1)
		return 1;
	if(fn[n] != 0)
		return fn[n];

	return fib_mem(n-1) + fib_mem(n-2);

}


int main()
{
	//printf("fib[%d]=%d\n", len, fib(len));
	//printf("fib[%d]=%d\n", len, fib_r(len));
	printf("fib[%d]=%d\n", len, fib_mem(len));
}
