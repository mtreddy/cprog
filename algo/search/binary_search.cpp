#include<iostream>
#define ARRAY_LEN 25

int data[25] = {25,22,23,21,19,24,18,20,17,14,16,13,15,12,10,11,9,7,8,6,4,5,3,1,2};
class BinarySearch{
    public:
        void swap(int *a, int *b);
        int partition(int *data, int lo, int hi);
        void quick_sort(int *data, int lo, int hi);
        int binary_search(int *data, int p, int q, int val);
        void print_data(int *data);
};
void BinarySearch::print_data(int *data)
{
    printf("\n");
    for(int i = 0; i < ARRAY_LEN; i++)
        printf(" %0d ", data[i]);
    printf("\n");
}

void BinarySearch::swap(int *a, int *b)
{
    int tmp = 0;
    tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}
void BinarySearch::quick_sort(int *data, int lo, int hi)
{
    int pi = 0;
    if(lo < hi) {
        pi =  partition(data, lo, hi);
        quick_sort(data,lo,pi-1);
        /*
         * pi position already in sorted order dont need to sort
         * which is why we pass pi-1 and pi+1
         */
        quick_sort(data,pi+1,hi);
    }
}
int BinarySearch::partition(int *data, int lo, int hi)
{
    int pivot;
    int i = 0, j = 0;
    pivot = data[hi];
    j = lo;
    for(i=lo; i<=hi-1;i++) {
        if(data[i] <= pivot) {
            swap(&data[i],&data[j]);
            j+=1;
        }
    }
    /*Swap pivot with new found max number which would be partition index.*/
    swap(&data[j],&data[hi]);
    return j;
}
int BinarySearch::binary_search(int *data, int p, int q, int val)
{
    int mid = 0;
    if(q >= 1) {
        mid = (p + (q - 1))/2;
        if(data[mid] == val) return mid;
        
        if(data[mid] > val) 
            return binary_search(data,  p, mid - 1, val);
        else
            return binary_search(data,  mid + 1, q, val);
    }
    return -1;
}
int main()
{
    class BinarySearch bs;
    bs.print_data(&data[0]);
    bs.quick_sort(data,0,24);
    bs.print_data(data);
    printf("found val %d\n", bs.binary_search(data, 0, 24, 24));
}
