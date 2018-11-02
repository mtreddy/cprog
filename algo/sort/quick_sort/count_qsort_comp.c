/*
 * gcc.c4.2.1-p4a.x86_64 -g3 quick_sort.c  -o quick_sort 
 *
 * Quick sort is devide and conquer algorithm. It first divides a large array into smaller sub-arrays: The low elements and the high 
 * elements. Quick sort can then recursively sort the sub-arrays.
 *
 * 1. Pick element, called pivot, from the array.
 * 2. Partitioning: reorder the array so that all elements with the values less than the pivot come before the pivot, 
 *    while all elements with values greater than the pivot come after it . After partitioning, the pivot is in its final poisiton.
 * 3. recursively apply the above steps to the sub sub-array of elements. whtih smaller values.
 *
 *  algorithm quicksort(A, lo, hi) is
 *      if lo < hi then
 *          p := partition(A, lo, hi)
 *          quicksort(A, lo, p – 1)
 *          quicksort(A, p + 1, hi)
 *  algorithm partition(A, lo, hi) is
 *      pivot := A[hi]
 *      i := lo        // place for swapping
 *      for j := lo to hi – 1 do
 *          if A[j] ≤ pivot then
 *              swap A[i] with A[j]
 *              i := i + 1
 *      swap A[i] with A[hi]
 *      return i
 */ 
#include<stdio.h>
#include "../sort_common.h"
#include "qdata.h"

#define DATASIZE 25
//int data[25] = {25,22,23,21,19,24,18,20,17,14,16,13,15,12,10,11,9,7,8,6,4,5,3,1,2};
int g_comp = 0;
/*
 * Loumuto partition scheme
 * Algorithm maintains the index to put the pivot in variable i and each time it finds an element 
 * less than or equal to pivot, this index is incremented and that element would be placed before 
 * the pivot. This schem is more compact and easy to understand, it is frequently used.
 */
int lomuto_partition(int *array, int lo, int hi)
{
    int pivot = 0;
    int i = 0, j = 0;
        g_comp += (hi - lo);
    pivot = array[hi];
    i = lo;
    for( j = lo; j <= hi-1; j++) {
        if(array[j] <= pivot) {
            swap(&array[j], &array[i]);
            //printf("Inside swap array[%d]=%d array[%d]=%d\n", j, array[j], i, array[i]);
            i= i + 1;
        }
    }
    swap(&array[i], &array[hi]);
    //printf("Outside swap array[%d]=%d array[%d]=%d\n", j, array[j], i, array[i]);
    return i;
}

int partition_pivot_hi(int *array, int lo, int hi)
{
    int pivot = 0;
    int i = 0, j = 0;
    pivot = array[hi];
    i = lo;
    for( j = lo; j <= hi-1; j++) {
        if(array[j] <= pivot) {
            swap(&array[j], &array[i]);
            //printf("Inside swap array[%d]=%d array[%d]=%d\n", j, array[j], i, array[i]);
            i= i + 1;
        }
    }
    swap(&array[i], &array[hi]);
    //printf("Outside swap array[%d]=%d array[%d]=%d\n", j, array[j], i, array[i]);
    return i;
}
int partition_pivot_lo(int *array, int lo, int hi)
{
    int pivot = 0;
    int i = 0, j = 0;
    pivot = array[lo];
    i = lo+1;
    for( j = lo+1; j <= hi-1; j++) {
        if(array[j] <= pivot) {
            swap(&array[j], &array[i]);
            //printf("Inside swap array[%d]=%d array[%d]=%d\n", j, array[j], i, array[i]);
            i= i + 1;
        }
    }
    swap(&array[i-1], &array[lo]);
    //printf("Outside swap array[%d]=%d array[%d]=%d\n", j, array[j], i, array[i]);
    return i;
}
int partition_pivot_med(int *array, int lo, int hi)
{
    int pivot = 0;
    int i = 0, j = 0;
    pivot = array[hi];
    i = lo;
    for( j = lo; j <= hi-1; j++) {
        if(array[j] <= pivot) {
            swap(&array[j], &array[i]);
            //printf("Inside swap array[%d]=%d array[%d]=%d\n", j, array[j], i, array[i]);
            i= i + 1;
        }
    }
    swap(&array[i], &array[hi]);
    //printf("Outside swap array[%d]=%d array[%d]=%d\n", j, array[j], i, array[i]);
    return i;
}

void quick_sort(int *array, int lo, int hi)
{
    int pi = 0;
    if(lo < hi) {
        pi = lomuto_partition(array, lo, hi);
        //printf("pi=%d\n", pi);
        quick_sort(array, lo, pi - 1);
        quick_sort(array, pi + 1, hi);
    }
}
/*
 * Hoare partition scheme:
 *  Two indices that start at the ends of the array being partitioned,
 *  then move toward each other, until they detect an inversion: pair of 
 *  elements, one greater than the pivot, one smaller, that are in the wrong order
 *  relative to each other. The inverted elements are then swapped. When indices
 *  meet algorithm stops and returns ihe final index.
 *  algorithm quicksort(A, lo, hi) is
 *
 *  if lo < hi then
 *      p := partition(A, lo, hi)
 *      quicksort(A, lo, p)
 *      quicksort(A, p + 1, hi)
 *  algorithm partition(A, lo, hi) is
 *      pivot := A[lo]
 *      i := lo – 1
 *      j := hi + 1
 *      loop forever
 *          do
 *              i := i + 1
 *          while A[i] < pivot
 *          
 *          do
 *              j := j – 1
 *          while A[j] > pivot
 *          
 *          if i >= j then
 *              return j
 *          
 *          swap A[i] with A[j]
 *
 */

int hoare_partition(int *array, int lo, int hi)
{
    int pivot = 0;
    int i=0,j=0;
    j = hi + 1;
    i = lo - 1;
    pivot = array[lo];
    while(1) {
        do{
            i = i + 1;
            //printf("i inc i=%d j=%d array[i]=%d pivot= %d \n", i, j, array[i], pivot);
        } while (array[i] < pivot);
        do{
            j = j - 1;
            //printf("i inc i=%d j=%d array[j]=%d pivot= %d \n", i, j, array[j], pivot);
        } while (array[j] > pivot);

        if( i >= j) {
            //printf("return i=%d j=%d\n", i, j);
            return j;
        }
        swap(&array[i], &array[j]);
        //printf("outside swap array[%d]=%d array[%d]=%d\n", j, array[j], i, array[i]);
    }
}
void quick_sort1(int *array, int lo, int hi)
{
    int pi = 0;
        //printf("outside pi=%d lo=%d hi=%d \n", pi, lo, hi);
    if(lo < hi) {
        g_comp += (hi - lo)-1;
        pi = hoare_partition(array, lo, hi);
        //printf("inside pi=%d lo=%d hi=%d \n", pi, lo, hi);
        //show_data_flat(sizeof(data)/(sizeof(int)), array);
        quick_sort1(array, lo, pi);
        quick_sort1(array, pi + 1, hi);
    }
}

int main(void)
{
    //show_data(sizeof(data)/(sizeof(int)), data);
    //quick_sort(data, 0, sizeof(data)/(sizeof(int)) - 1);
    //quick_sort1(data, 0, sizeof(data)/(sizeof(int)) - 1);
    quick_sort(data, 0, 99);
    //show_data(10, data);
    printf("No of comparisions %d \n", g_comp);
    //show_data(sizeof(data)/(sizeof(int)), data);
}
/*  Algo explained
 * pi =0 0-24
 * pi=23 0-23 24-24
 * pi=1 1-1 2-23
 * pi=20 (1-20) (21-23)
 * pi=1 (1-1) (2-20)
 * pi=2 (2-2) (3-20)
 * pi=19 (3-19)
 * pi=3  (3-3) (4-19)
 * pi=17 (4-17)
 * pi=4 (4-4) (5-17)
 * pi=5 (5-5)(6-17)
 * pi = 16 (5-16)
 * pi = 6 (6-6) (7-16)
 * pi = 7 (7-7) (8-16)
 * pi = 15 (8-15)
 * 
 *
 *
 
 */
