#include<stdio.h>

void move(int n, int start, int finish, int temp)
{
    if(n > 0) {
        move(n-1, start, temp, finish);
        printf("Move %d from start %d to finish %d\n", n-1, start, finish);
        move(n-1, temp, finish, start);
    }
}
int main()
{
    move(4, 1 , 3 , 2);
}
