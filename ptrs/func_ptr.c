#include<stdio.h>

void print_func(int val)
{
    printf("Val=%d\n", val);
}

int main()
{
    void (*fptr)(int) = &print_func;
    (*fptr)(100);
    fptr(2000);
}
