/*
 * Bubble sort also called sinking sor.
 * Copares each pair of adjacent intems and swaps them if they are in the wrong  order.
 */
#include<stdio.h>
#include "sort_common.h"

#define DATASIZE 25
int data1[25] = {25,22,23,21,19,24,18,20,17,14,16,13,15,12,10,11,9,7,8,6,4,5,3,1,2};

void print_array(int len, int *data) {
    int i = 0;
    for(i = 0; i < len; i++)
        printf(" %3d ", data[i]);
    printf("\n");
}
int main(int argc, char **argv)
{
	int len = DATASIZE;
    int i = 0, j = 0;
    int tmp = 0;

    print_array(len, data1);
    for(i=0; i< DATASIZE; i++){
        for(j = i+1; j < DATASIZE; j++) {
            if(data1[i] > data1[j]) {
                tmp = data1[i];
                data1[i] = data1[j];
                data1[j] = tmp; 
            }
        }
        print_array(len, data1);
    }
	//show_data(len, data1);

}
