/*
 * gcc.c4.2.1-p4a.x86_64 -g3 heap_ds.c  -o heap_ds 
 *   Heap data structure or priority queue
 * Heap is specialized tree based data structure that satisifies the heap property. 
 * There are two types of heaps, max heap and min heap. In Max heap, the keys of parent nodes 
 * are always greater than or equal to those of the children. In min heap, theu leys of parent 
 * nodes are less than or equal to those of the children.
 *
 *  children are places at 2i and 2i+1 element from the parent.
 */

#include<stdio.h>

int array[500];
int heap_size = 0;

static void show_data_flat(int len) {  
    int i; for(i=0; i < len; i++) {
        printf(" %2d ", *(unsigned int *)(array + i)); 
        if((i%15 == 0) && (i != 0))
            printf("\n");
    }
        
    printf("\n");
}
void heapify(int heap_len)
{
}
int heap_len()
{
    int len = 0;
    return len;
}
int heap_insert_ele_max( int val)
{
    int indx = 0;
        
    heap_size++;
    array[heap_size] = val;
    if(heap_size == 1) {
        return 0;
    }
    indx = heap_size;
    while(array[indx/2] < val)
    {
        printf("indx=%d\n array[indx]=%d array[indx/2]=%d\n", indx, array[indx], array[indx/2]);
        array[indx] = array[indx/2];
        indx = indx/2;
        if(indx == 1)
            break;
    }
    array[indx] = val;
    return 0;
}
int heap_insert_ele( int val)
{
    int indx = 0;
    heap_size++;
    array[heap_size] = val;
    indx = heap_size;
    while(array[indx/2] > val)
    {
        array[indx] = array[indx/2];
        indx = indx/2;
    }
    array[indx] = val;
    return 0;
}
int heap_del_min(void)
{
    int indx, last_ele, child, min_ele;
    last_ele = array[heap_size--];
    min_ele = array[1];
    for(indx = 1; indx < heap_size; indx = child) {
        child = indx * 2;
        if(child != heap_size && array[child+1] < array[child]) {
            child++;
        }
        if(last_ele > array[child]) {
            array[indx] = array[child];
        } else {
            break;
        }
    }
    array[indx] = last_ele;
    return min_ele;
}


void heap_delete_ele( int val, int len)
{
    return;
}

int main(void) {
    int len = 0 ;

    if(1) {
        heap_insert_ele(10);
        heap_insert_ele(30);
        heap_insert_ele(15);
        heap_insert_ele(25);
        heap_insert_ele(05);
        show_data_flat(heap_size+1);
        printf("min:%d\n",heap_del_min());
        show_data_flat(heap_size+1);
        printf("min:%d\n",heap_del_min());
        show_data_flat(heap_size+1);
    } else {
        heap_insert_ele_max(10);
        heap_insert_ele_max(30);
        heap_insert_ele_max(15);
        heap_insert_ele_max(25);
        heap_insert_ele_max(05);
    }
}
