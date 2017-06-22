#include<stdio.h>
//g++  cut_rod.c -o cut_rod
int len[] = {1, 5, 8, 9, 10, 17,17, 20};
int max(int a, int b)
{
    return a > b ? a : b;
}

int cut_rod(int *price, int n)
{
    if(n <= 0)
        return 0;
    int max_val = 0;

    for (int i=0; i < n; i++) 
        max_val = max(max_val, price[i] + cut_rod(price, n-i-1));
    return max_val;
}
int main ()
{
    int size = sizeof(len)/sizeof(len[0]);
    printf(" Maximum attainable value is %d\n", cut_rod(len, size));
    return 0;
}
