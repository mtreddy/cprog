#include <stdio.h>

int main()
{
    char str[] = "5GT/s";
    int val ;


    sscanf(str, "%dGT/s", &val);
    printf("val %d\n",val);
}
