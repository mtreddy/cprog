/*
 * gcc.c4.2.1-p4a.x86_64 -g3 selection_sort.c  -o selection_sort 
 *   Performance: O(n^2)
 */
#include<stdio.h>
#include<malloc.h>
#include "sort_common.h"
#define DATASIZE 25
int data1[25] = {25,22,23,21,19,24,18,20,17,14,16,13,15,12,10,11,9,7,8,6,4,5,3,1,2};
void swap(int *a, int *b)
{
    int tmp = 0;

    tmp = *a;
    *a = *b;
    *b = tmp;
}
int main()
{
    int i = 0, j=0;
    int *data;
    int *ddata;
    int tmp = 0;
    //data = (int *)malloc(sizeof(int)*DATASIZE);
    //ddata = (int *)malloc(sizeof(int)*DATASIZE);
    data = &data1[0]; 
    //fill_data(DATASIZE, data);
    /*print input list*/
    for(i=0;i<DATASIZE; i++)
    printf("inputdata[%d]=%d\n", i, data[i]);
    /* print intermidiate list*/
    for(i=0;i<DATASIZE;i++) {
        int iMin = i;
        for(j=i + 1; j <DATASIZE; j++) {
            if(data[iMin] > data[j]) {
                iMin = j;
            }
        }
        if(iMin != i)
            swap(&data[i], &data[iMin]);
    }
    
    /* print final list*/
    for(i=0;i<DATASIZE; i++)
    printf("output data[%d]=%d\n", i, data[i]);
}
