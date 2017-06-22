/*
 * This is a generic function call which accepts
 * 1. Address range or address bits
 * 2. Pattern
 *
 * What is the purpose of mem test?
 * To eliminate
 * 1. Bad soldering
 * 2. Cross-Connected address/data lines?
 * 3. Miss matched impedence for DDR data lines
 * 4. Mirroring issues
 *
 *  Address:
 *  1. Pass a data structure explaining how address bits should change
 *  2. Padd a data structure explaining how data bits should change
 *
 * Conditions:
 *  1. Make sure data not cached
 */
#include <stdio.h>
#include <malloc.h>
typedef unsigned char uchar ;
typedef unsigned int uint32 ;
typedef unsigned long ulong;
ulong mem_test_data_lines(ulong addr)
{
    ulong pattern = 1;
    
    volatile ulong *tmp = (ulong *)addr;
    

    while(pattern <<= 1) {
        *tmp = pattern;

        if(*tmp != pattern)
            return pattern;
    }

    return 0;
}
unsigned int mem_test_addr_lines(unsigned long addr, int len)
{
    int i = 0;
    int ret = 0;
    volatile unsigned long *tmp = addr;
    int pattern = 0xAAAAAAAA;
    int apattern = 0x55555555;
    int offset = 0;
    int aoffset = 0;

        printf("addr mask 0x%lx, len 0x%x\n ", addr, len);
    for(offset=1; (len) >= offset; offset <<=1) {
        *(tmp + offset) = pattern;
        printf("addr 0x%lx, data 0x%x offset = 0x%x \n ", (tmp + offset), *(tmp+offset), offset);
    }
    
    /*Check for the lines which are stuck high*/
    aoffset = 0;
    //offset = 0;
    *(tmp + aoffset) = apattern;
    for(offset = 1; (len) >= offset; offset <<= 1) {
       if(*(tmp + offset) != pattern) {
        printf("addr 0x%lx, data 0x%x offset = 0x%x \n ", (tmp + offset), *(tmp+offset), offset);
           return (tmp + offset);
       }
    }

    /*Check for the addr lines which are stuck low or shorted*/
    *(tmp + aoffset) = pattern;

    for(aoffset = 1; (len) >= aoffset; aoffset <<= 1) {
        *(tmp + aoffset) = apattern;
        if(*tmp != pattern)
            return (tmp + offset);

        for(offset = 1; (len) >= offset; offset <<= 1) {
            printf("addr 0x%lx, data 0x%x offset = 0x%x \n ", (tmp + offset), *(tmp+offset), offset);
            printf("addr 0x%lx, data 0x%x aoffset = 0x%x \n ", (tmp + aoffset), *(tmp+aoffset), aoffset);
            if((*(tmp + offset) != pattern) &&(offset != aoffset))
                return (tmp + offset);
        }
        *(tmp + aoffset) = pattern;

    }

    return (NULL);
}

int main()
{
    int len = 0x1000;
    unsigned long *addr = malloc(sizeof(int) * len);
    printf("passing addr 0x%lx\n",addr);
    
    if(mem_test_addr_lines(addr,len))
        printf("Addr line test Failed\n");
    else
        printf("Addr line test passed\n");

    if(mem_test_data_lines(addr))
        printf("Data line test Failed\n");
    else
        printf("Data line test passed\n");

    free(addr);
}
