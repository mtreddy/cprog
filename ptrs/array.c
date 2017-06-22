#include<stdio.h>

int main()
{
    int a[5] = {1,2,3,4,5};
    int *ptr;

    printf("a[0]=0x%x &a[0]=0x%x a=0x%x\n", a[0], &a[0], a);
    ptr = a;
    printf("*ptr=0x%x ptr=0x%x\n", *ptr, ptr);
}
