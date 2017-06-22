#include<stdio.h>

int main()
{
    system("exec sleep 2");
    printf("Slept 2 secs\n");
    system("sleep 3");
    printf("Slept 3 secs\n");
}
