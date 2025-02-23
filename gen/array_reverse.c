/*
 * Program to reverser integer array
 * gcc array_reverse.c -o array_reverse
 */
#include<stdio.h>

int array[] = {11,22,33,44,55};

void array_reverse(int *arr , size_t sz) {
	for(int ind = 0; ind < sz/2; ind++) {
		int tmp = 0;
		tmp = arr[ind];
		if(ind != 0) {
			tmp = arr[ind];
			arr[ind] = arr[sz - ind];
			arr[sz - ind] = tmp;
		} else {
			tmp = arr[0];
			arr[0] = arr[sz];
			arr[sz] = tmp;
		}
	}
}
void array_print(int *arr, size_t sz) {
	printf("\n");
	for(int ind = 0; ind <= sz; ind++) {
		printf("arr[%d]=%d ", ind, arr[ind]);
	}
	printf("\n");
}
int main(){
	size_t asz = sizeof(array)/sizeof(int) - 1;
	array_print(array, asz);
	array_reverse(array, asz);
	array_print(array, asz);
}
