#include <stdio.h>

#define round_t(val) \
        ( (((float)val - (int)val) < (float)0.5) ? ((int)val) : ((int)val + 1) )
int main(void)
{
    float val1 = 2.51, val2 = 2.49;

    printf("rounded value for %f is %d\n", val1, round_t(val1));
    printf("rounded value for %f is %d\n", val2, round_t(val2));
    return;
}


