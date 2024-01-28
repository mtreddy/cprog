/*
 * Copyright 2024
 *
 */
#include<stdio.h>

#define pos_val(x) x<0?(-x):x

int main(void)
{
    float x = 10.1;

    x = 100.2;
    printf("%f\n", (fabsf(-10.202) - fabsf(-10.301)));
}
