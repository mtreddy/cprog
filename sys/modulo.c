#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int val = 0;
    val = 200;
    printf("200%8=0x%x\n", val%8);
    val = 201;
    printf("201%8=0x%x\n", val%8);
}
