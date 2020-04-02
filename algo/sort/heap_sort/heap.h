/*
 * This contains the aarrays
 */
#include "../sort_common.h"
int array[] = {20,2,200,5,500,50,70, 7, 700,90, 9,900,80,8, 800};

void print_array(int arr[], int size)
{
	int i = 0;

	for(i=0; i<size; i++){
		printf("%5d ", arr[i]);
	}
	printf("\n");
}
