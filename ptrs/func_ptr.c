#include<stdio.h>

void print_double(void *val, int i)
{
    printf("Print val=%f\n", *(float *)((int*)val+i));
}

void print_char(void *ch, int i)
{
    printf("Print ch=%c\n", *(char *)(ch+i));
}

void print_int(void *val, int i)
{
    printf("Print val=%x\n", *(int*)((int *)val+i));
}

void print_func(int len, void *arr, void (*pr)(void *val, int ind)) {
    int i = 0;
    for(i=0; i<len; i++) {
        pr(arr,i);
    }
}
int main()
{
    int arr[5] = {1,2,3,4,5};
    float darr[5] = {1.1,2.2,3.3,4.4,5.5};
    char carr[5] = {'a', 'b', 'c', 'd', 'e'};
    for(int i = 0; i < 5; i++){
        printf("Print val=%d\n", arr[i]);
    }
    for(int i = 0; i < 5; i++){
        printf("Print val=%f\n", darr[i]);
    }
    print_func(5, arr, print_int);
    print_func(5, carr, print_char);
    print_func(5, darr, print_double);
}
