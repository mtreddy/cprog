typedef unsigned char uchar ;
typedef unsigned int uint32 ;
typedef unsigned long ulong;
static int pattern = 0xAAAAAAAA;
static int apattern = 0x55555555;
ulong data_fill_pattern(ulong addr, int len, int reverse)
{
    int i = 0;
    for(i = 0; i < len; i+=8) {
        if(reverse){
            *(volatile uint32 *)(addr + i) = pattern;
            *(volatile uint32 *)(addr + i + 4) = apattern;
        } else {
            *(volatile uint32 *)(addr + i) = apattern;
            *(volatile uint32 *)(addr + i + 4) = pattern;
        }
    }
}
ulong data_read_pattern(ulong addr, int len, int reverse)
{
    int i = 0;
    for(i = 0; i < len; i+=8) {
        if(reverse) {
            if(*(volatile uint32 *)(addr + i) != pattern)
                printf("Pattern missmatch at 0x%llx\n",addr + i);
            if(*(volatile uint32 *)(addr + i + 4) != apattern)
                printf("Pattern missmatch at 0x%llx\n",addr + i + 4);
        } else {
            if(*(volatile uint32 *)(addr + i) != apattern)
                printf("Pattern missmatch at 0x%llx\n",addr + i);
            if(*(volatile uint32 *)(addr + i + 4) != pattern)
                printf("Pattern missmatch at 0x%llx\n",addr + i + 4);
        }
    }
    printf("Test PASSED for addr = 0x%llx to addr = 0x%llx len 0x%llx\n",addr, (addr + i), len);
    return 0;
}
void mem_march_test(ulong addr, uint32 len)
{
    /* Write first*/
    data_fill_pattern(addr,len, 0);
    /* Then read to check */
    data_read_pattern(addr,len, 0);
    /* Write reverse bit pattern*/
    data_fill_pattern(addr,len, 1);
    /* Then read to check reverse pattern */
    data_read_pattern(addr,len, 1);
}

int main(void)
{
    unsigned int *addr;


    addr = (unsigned int *)malloc(256 * 1024 * 1024);

    mem_march_test(addr,256 * 1024 * 1024);
}
