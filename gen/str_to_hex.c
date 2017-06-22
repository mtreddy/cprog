#include<stdio.h>
#include<string.h>

int main(int argc, char** argv[])
{
    unsigned long phys_addr = 0;
    sscanf(argv[1],"0x%x",&phys_addr);
    printf("%x\n",phys_addr);
}
