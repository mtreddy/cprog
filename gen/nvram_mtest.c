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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <errno.h> 
#define MAP_SIZE    0x400000
#define MAP_MASK (MAP_SIZE - 1)
#define FATAL do { fprintf(stderr, "Error at line %d, file %s (%d) [%s]\n", \
        __LINE__, __FILE__, errno, strerror(errno)); exit(1); } while(0)
typedef unsigned char uchar ;
typedef unsigned int uint32 ;
typedef unsigned long ulong;
typedef unsigned long long uint64;
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
unsigned int mem_test_addr_lines(volatile unsigned long addr, int len)
{
    int i = 0;
    int ret = 0;
    volatile unsigned long *tmp = addr;
    volatile unsigned long *tmp1 = addr;
    int pattern = 0xAAAAAAAA;
    int apattern = 0x55555555;
    int offset = 0;
    int aoffset = 0;

        printf("addr mask 0x%lx, len 0x%x\n ", addr, len);
    for(offset=2; (len) >= offset; offset <<=1) {
        *(volatile uint64*)(tmp + offset) = pattern;
        printf("addr 0x%lx, data 0x%x offset = 0x%x \n ", (tmp + offset), *(volatile uint64*)(tmp+offset), offset);
    }
    
    /*Check for the lines which are stuck high*/
    aoffset = 0;
    //offset = 0;
    *(volatile uint64*)(tmp + aoffset) = apattern;
    static int cnt = 0;
    for(offset = 2; (len) >= offset; offset <<= 1) {
       if(*(tmp + offset) != pattern) {
                //printf("addr 0x%lx, data 0x%x offset = 0x%x \n ", (tmp + offset), *(tmp+offset), offset);
                printf("Addr lines stuck high:Exepected 0x%llx but found 0x%llx at addr 0x%llx\n", pattern, *(tmp + offset), (tmp+offset));
                cnt++;
           if(cnt)
                tmp1 = (tmp+offset) ;
       }
    }

    /*Check for the addr lines which are stuck low or shorted*/
    *(volatile uint64*)(tmp + aoffset) = pattern;

    for(aoffset = 2; (len) >= aoffset; aoffset <<= 1) {
        *(volatile uint64*)(tmp + aoffset) = apattern;
        if(*tmp != pattern)
            return (tmp + offset);

        for(offset = 2; (len) >= offset; offset <<= 1) {
            //printf("addr 0x%lx, data 0x%x offset = 0x%x \n ", (tmp + offset), *(tmp+offset), offset);
            //printf("addr 0x%lx, data 0x%x aoffset = 0x%x \n ", (tmp + aoffset), *(tmp+aoffset), aoffset);
            if((*(tmp + offset) != pattern) &&(offset != aoffset)) {
                printf("Stuck low Exepected 0x%llx but found 0x%llx 0x%llx \n", pattern, *(tmp + offset), (tmp + offset));
                return (tmp + offset);
            }
        }
        *(volatile uint64*)(tmp + aoffset) = pattern;

    }

           if(cnt)
               return (unsigned long)tmp1;
    return 0;
}

int main(int argc, char** argv)
{
    int len = 0x1000;
    volatile unsigned long *addr = NULL; // = malloc(sizeof(int) * len);
    volatile unsigned long phys_addr = 0;
    int fd = 0;
    volatile unsigned long val = 0;
    /*Base always hex*/
    sscanf(argv[1],"0x%x",&phys_addr);
    if(!phys_addr) {
        printf("Invalid Phys address 0x%x\n", phys_addr);
        return -1;
    }
    sscanf(argv[2],"0x%x", &len);
    if(!len) {
        printf("Invalid len 0x%x\n", len);
        return -1;
    }
    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) FATAL; 
    addr = mmap(0, MAP_SIZE , PROT_READ | PROT_WRITE, MAP_SHARED, fd, phys_addr & (~(len - 1)));

    printf("passing addr 0x%lx len 0x%x \n", addr, len);
    
    val = mem_test_addr_lines(addr,len);
    if(val)
        printf("Addr line test Failed at 0x%llx \n", val);
    else
        printf("Addr line test passed\n");

    val = mem_test_data_lines(addr);
    if(val)
        printf("Data line test Failed at 0x%llx \n", val);
    else
        printf("Data line test passed\n");

   // free(addr);
}
