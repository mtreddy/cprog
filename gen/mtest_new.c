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
#include <time.h>
#include <sys/timeb.h>
//#define DEBUG_MTEST 1
#ifdef DEBUG_MTEST
#define dbgpr   printf
#else
#define dbgpr
#endif
typedef unsigned char uchar ;
typedef unsigned int uint32 ;
typedef unsigned long ulong;
static int pattern = 0xAAAAAAAA;
static int apattern = 0x55555555;
static int fill_len = 2 * 1024 * 1024; //2 * 1024 * 1024 ; //1024 * 1024 * 1024; /*This has to be big enough to flush out the L1 and L2 cache*/
static unsigned long *fill_addr;
static int tmeas1 = 0;
static int tmeas2 = 0;
ulong data_fill_pattern(ulong addr, int len)
{
    struct timeb t1,t2;
    if(tmeas1 == 0)
        time(&t1);
    int i = 0;
    for(i = 0; i < len; i+=8) {
        *(volatile uint32 *)(addr + i) = pattern;
        *(volatile uint32 *)(addr + i + 4) = apattern;
        if(i <= 64) {
        dbgpr("(addr + i) 0x%llx (addr + i + 4) 0x%llx ", (volatile uint32 *)(addr + i), (volatile uint32 *)(addr + i + 4));
        dbgpr("*(addr + i) 0x%llx *(addr + i + 4) 0x%llx \n", *(volatile uint32 *)(addr + i), *(volatile uint32 *)(addr + i + 4));
        }
    }
    if(tmeas1 == 0) {
        time(&t2);
        printf("Write time t1-t2=0x%d mill Seconds\n",(t1.millitm-t2.millitm));
        printf("Write time t1-t2=0x%d  Seconds\n",(t1.time - t2.time));

        tmeas1 = 1;
    }
}
ulong data_read_pattern(ulong addr, int len)
{
    struct timeb t1,t2;
    if(tmeas2 == 0)
        time(&t1);
    int i = 0;
    for(i = 0; i < len; i+=8) {
        if(*(volatile uint32 *)(addr + i) != pattern)
            dbgpr("Pattern missmatch at 0x%llx\n",addr + i);
        if(*(volatile uint32 *)(addr + i + 4) != apattern)
            dbgpr("Pattern missmatch at 0x%llx\n",addr + i + 4);
    }
    if(tmeas2 == 0) {
        time(&t2);
        printf("Read time t1-t2=0x%d mill Seconds\n",(t1.millitm-t2.millitm));
        printf("Read time t1-t2=0x%d  Seconds\n",(t1.time - t2.time));

        tmeas2 = 1;
    }
}
/* 
 * flush L1 data chache lines 
 * If L2 is in write back mode we need to flush L2 cache 
 * too. Once flushed need to invalidate those lines to makes
 * sure data was not fetched from cache during read time.
 */
#if 0
void l1_cache_line_flush_inv(ulong addr,uint32 len)
{
    /*to be implemented*/
}
#else
void l1_cache_line_flush_inv(ulong addr, uint32 len)
{
    data_fill_pattern(addr,len);
    data_read_pattern(addr,len);
}
#endif
ulong mem_test_data_lines(ulong addr)
{
    ulong pattern = 1;
    
    volatile ulong *tmp = (ulong *)addr;
    

    while(pattern <<= 1) {
        *tmp = pattern;

        l1_cache_line_flush_inv(fill_addr, fill_len);
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
    int offset = 0;
    int aoffset = 0;

        dbgpr("addr mask 0x%lx, len 0x%x\n ", addr, len);
    for(offset=1; (len) >= offset; offset <<=1) {
        l1_cache_line_flush_inv(fill_addr, fill_len);
        *(tmp + offset) = pattern;
        dbgpr("addr 0x%lx, data 0x%x offset = 0x%x \n ", (tmp + offset), *(tmp+offset), offset);
    }
    
    /*Check for the lines which are stuck high*/
    aoffset = 0;
    //offset = 0;
    *(tmp + aoffset) = apattern;
    for(offset = 1; (len) >= offset; offset <<= 1) {
       if(*(tmp + offset) != pattern) {
        dbgpr("addr 0x%lx, data 0x%x offset = 0x%x \n ", (tmp + offset), *(tmp+offset), offset);
           return (tmp + offset);
       }
    }

    /*Check for the addr lines which are stuck low or shorted*/
    *(tmp + aoffset) = pattern;

    for(aoffset = 1; (len) >= aoffset; aoffset <<= 1) {
        *(tmp + aoffset) = apattern;
        l1_cache_line_flush_inv(fill_addr, fill_len);
        if(*tmp != pattern)
            return (tmp + offset);

        for(offset = 1; (len) >= offset; offset <<= 1) {
            dbgpr("addr 0x%lx, data 0x%x offset = 0x%x \n ", (tmp + offset), *(tmp+offset), offset);
            dbgpr("addr 0x%lx, data 0x%x aoffset = 0x%x \n ", (tmp + aoffset), *(tmp+aoffset), aoffset);
            if((*(tmp + offset) != pattern) &&(offset != aoffset))
                return (tmp + offset);
        }
        *(tmp + aoffset) = pattern;
        l1_cache_line_flush_inv(fill_addr, fill_len);

    }

    return (NULL);
}

int main()
{
    int len = 0x1000;
    unsigned long *addr = malloc(sizeof(int) * len);
    fill_addr = malloc(sizeof(int) * fill_len);
    dbgpr("passing addr 0x%lx\n",addr);
    dbgpr("passing fill_addr 0x%lx\n",fill_addr);
    
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
