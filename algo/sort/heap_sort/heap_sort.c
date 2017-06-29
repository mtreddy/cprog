/*
 * gcc.c4.2.1-p4a.x86_64 -g3 heap_sort.c  -o heap_sort 
 * Heap Sort:
 *  It has two steps.
 *  1. Build heap out of the data.
 *  2. A sorted array is created by repeatedly removing largest element fromt the heap and inserting into the array. 
 *     The heap is updated after each removal to maintain the heap.
 *
 *     Algorithm:
 *     1. Call buildMaxHeap() function on the list also referred as heapify(), this builds a heap from a list in O(n) operations.
 */
#include<stdio.h>
#include "sort_common.h"
int array[500];
int heap_size = 0;
/*
static void show_data_flat(int len) {  
    int i; for(i=0; i < len; i++) {
        printf(" %2d ", *(unsigned int *)(array + i)); 
        if((i%15 == 0) && (i != 0))
            printf("\n");
    }
    printf("\n");
}
*/
void heapify(int n, int i)
{
    int largest = i;
    int l = 2*i+1;
    int r = 2*i+2;

    /* If left child is largest*/
    if(l < n && array[l] > array[largest])
        largest = l;
    /* If right child is largest */
    if(r < n && array[r] > array[largest])
        largest = r;
    /* If largest is not root */
    if(largest != i) {
        swap(&array[i], &array[largest]);
        /*recursively heapify the affected sub tree*/
        heapify(n, largest);
    }
}

void heap_sort(int n)
{
    int i = 0;
    for (i = heap_size - 1; i>= 0 ; i-- ) {
        /*Move the root to array end*/
        swap(&array[0],&array[i]);
        heapify(i,0);
    }
}
void heap_insert(int num)
{
    int indx, last = 0;
    array[heap_size++] = num;
    indx = heap_size/2;  /* Initial parent node*/
    last = heap_size; /* Initial child node*/
    while( indx > 0) {
        /*Compare number with parent node value*/
        if(array[indx - 1] <= num) {
            /* replace child node with parent node value*/
            array[last - 1] = array[indx - 1];
            /*Store number in parent node*/
            array[indx - 1] = num;
    //            printf("IN :indx=%d array[indx -1 ]=%d array[indx]=%d \n", indx, array[indx - 1], array[indx]);
        }
        /*Update child node with last parent node*/
        last = indx;
        /*Update to new parent node*/
        indx = indx/2; 
    }
     //   printf("OUT:heap_size=%d indx=%d array[indx]=%d\n", heap_size, indx, array[indx]);
}
int main()
{
    heap_insert(53);
    heap_insert(71);
    heap_insert(11);
    heap_insert(23);
    heap_insert(47);
    heap_insert(91);
    printf("Tree in heap mode\n");
    show_data_flat(heap_size, array);
    heap_sort(heap_size);
    printf("Sorted Tree from  heap \n");
    show_data_flat(heap_size, array);
}
