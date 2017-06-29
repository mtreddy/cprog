#include "iostream"
int arr[25] = {25,22,23,21,19,24,18,20,17,14,16,13,15,12,10,11,9,7,8,6,4,5,3,1,2};
void swap(int *a, int *b)
{
    int tmp = 0;
    tmp = *a;
    *a = *b;
    *b = tmp;
}
class qsort {
    public:
    int partition(int *arr, int p, int q);
    void qsort_1(int *arr, int p, int q);
};
int qsort::partition(int *arr, int p, int r)
{
    int pivot = arr[r];
    int i =0, j = 0;
    i = p;
    for(j = p; j < r; j++) {
        if(arr[j] <= pivot){
            swap(&arr[i], &arr[j]);
            i += 1;
        }
    }
    swap(&arr[i], &arr[j]);
    return i;
}

void qsort::qsort_1(int *arr, int p, int r)
{
    int q = 0;
    if (p < r) {
        q = partition(arr, p, r);
        qsort_1(arr, p, q-1);
        qsort_1(arr, q+1, r);
    }
}

int main()
{
    class qsort qs;
    int p = 0;
    int q = sizeof(arr)/sizeof(int) - 1;
    printf("p=%d q=%d\n", p, q);
    for(int i = 0; i <= q; i++) {
        printf("arr[%d]=%d\n", i, arr[i]);
    }
    qs.qsort_1(arr,0, q);
    for(int i = 0; i <= q; i++) {
        printf("arr[%d]=%d\n", i, arr[i]);
    }
}
