#include<stdio.h>

void swap(int *v1, int *v2) {
	*v1 = *v1 + *v2;
	*v2 = *v1 - *v2;
	*v1 = *v1 - *v2;
}

int main(void) {
	int var1 = 100;
	int var2 = 200;

	printf("var1=%d var2=%d\n", var1, var2);
	swap(&var1, &var2);
	printf("var1=%d var2=%d\n", var1, var2);
}
