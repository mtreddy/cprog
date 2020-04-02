#include<stdio.h>
#include "heap.h"

void print_array(int arr[], int size);
int array[];
//int array[] = {12, 11, 13, 5, 6, 7}; 

int heap_size = 0;

void heapify(int n, int i)
{
    int largest = i;
    int l = 2*i+1;
    int r = 2*i+2;
	//printf("%s n-%d l-%d r-%d i-%d\n", __func__, n, l, r, i);
    /* If left child is largest*/
    if(l < n && array[l] > array[largest])
        largest = l;
    /* If right child is largest */
    if(r < n && array[r] > array[largest])
        largest = r;
    /* If largest is not root */
    if(largest != i) {
		//printf("sawpping %5d %5d i=%2d largest=%2d\n", array[i], array[largest], i, largest);
        swap(&array[i], &array[largest]);
		//print_array(array, n);
        /*recursively heapify the affected sub tree*/
        heapify(n, largest);
    }
}
void heap_sort(int n)
{
    int i = 0;

    for (i= (n/2)-1;i >= 0; i--) {
		heapify(n , i);
	}
    for (i= n-1 ;i >= 0; i--) {
        /*Move the root to array end*/
		//printf("i=%d\n",i);
		swap(&array[0],&array[i]);
		//print_array(array, n);
        heapify(i, 0);
    }
}

int main()
{
	heap_size = sizeof(array)/sizeof(int);
	print_array(array, heap_size);
	heap_sort(heap_size);
	print_array(array, heap_size);
}
