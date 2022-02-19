/*
 * gcc.c4.2.1-p4a.x86_64 -g3 iter.c -o iter
 */
#include<stdio.h>

void print_series(int n1, int n2)
{
    int i = 0;
    for (i = n1; i < n2; i++ ) {
        printf("%d\n",i);
    }
}

void print_recur_series(int n1, int n2)
{
    if(n1 <  n2) {
        print_recur_series(n1+1,n2);
    }
        printf("R:%d\n",n1);
}

int main(void)
{
    //print_series(10,20);
    print_recur_series(10,20);
}
