#include <stdio.h>
#include <math.h>

int main() {
    float fvboot = 0;
    float fvout_diff = 0;
    unsigned int vboot = 0x85;
    int percent = 1;

    fvboot = 1 + ((float)vboot - 0x97) * 0.005;

    printf("fvboot value is %2f\n", fvboot);
    fvout_diff = ceil((((double)percent * (double)fvboot)/0.005) * 100);                                          
    printf(" - fvout_diff value is %d\n", fvout_diff);
    return fvout_diff;
}
