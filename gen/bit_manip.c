//gcc.c4.2.1-p4.x86_64 bit_manip.c  -o bit_manip
#include <stdio.h>

unsigned int mask = 0xFFFFFFFF;

unsigned int set_bit(int bit_no, int ena_disa)
{
    unsigned int val;
    val = mask;
    printf("before--val=0x%x\n",val);
    val = (val & (~(1 << (bit_no))));
    val = val | (ena_disa << (bit_no));
    printf("after val=0x%x\n",val);
}
int main(){
    set_bit(1,0);
    set_bit(1,1);
    set_bit(15,0);
}
 
