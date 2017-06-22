/*
 * What is the purpose of mem test?
 * To eliminate
 * 1. Bad soldering
 * 2. Cross-Connected address/data lines?
 * 3. Miss matched impedence for DDR data lines
 * 4. Mirroring issues
 *
 */
#include <stdio.h>
#include <malloc.h>
typedef unsigned char uchar ;
typedef unsigned int uint32 ;
typedef unsigned long ulong;
/* 
 * flush L1 data chache lines 
 * If L2 is in write back mode we need to flush L2 cache 
 * too. Once flushed need to invalidate those lines to makes
 * sure data was not fetched from cache during read time.
 */
void l1_cache_line_flush_inv(ulong addr)
{
    /*to be implemented*/
}
ulong mem_test_data_lines(ulong addr)
{
    ulong pattern = 1;
    
    volatile ulong *tmp = (ulong *)addr;
    

    while(pattern <<= 1) {
        *tmp = pattern;
        /*flush and invalidate cache*/
        l1_cache_line_flush_inv(addr);
        if(*tmp != pattern)
            return pattern;
    }

    return 0;
}
ulong mem_test_addr_lines(ulong addr, int len)
{
    int i = 0;
    int ret = 0;
    volatile ulong *tmp = addr;
    int pattern = 0xAAAAAAAA;
    int apattern = 0x55555555;
    int offset = 0;
    int aoffset = 0;

    for(offset=1; (addr + len) > offset; offset <<=1) {
        /*flush and invalidate cache*/
        l1_cache_line_flush_inv(tmp + offset);
        *(tmp + offset) = pattern;
    }
    
    /*Check for the lines which are stuck high*/
    aoffset = 0;
    //offset = 0;
    *(tmp + aoffset) = apattern;
    for(offset = 1;(addr + len) > offset; offset <<= 1) {
       if(*(tmp + offset) != pattern) {
           return (tmp + offset);
       }
    }

    /*Check for the addr lines which are stuck low or shorted*/
    *(tmp + aoffset) = pattern;

    for(aoffset = 1; (addr + len) > aoffset; aoffset <<= 1) {
        *(tmp + aoffset) = apattern;
        l1_cache_line_flush_inv(tmp + aoffset);
        if(*tmp != pattern)
            return (tmp + offset);

        for(offset = 1; (addr + len) < offset; offset <<= 1) {
            if((*(tmp + offset) != pattern) &&(offset != aoffset))
                return (tmp + offset);
        }
        *(tmp + aoffset) = pattern;
        l1_cache_line_flush_inv(tmp + aoffset);

    }

    return (NULL);
}

int main()
{
    int len = 0x1000;
    ulong *addr = malloc(sizeof(int) * len);
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
