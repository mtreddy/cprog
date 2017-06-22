#include <stdio.h>
typedef unsigned long long uint64_t;
int bit_manipulation(void);
int main()
{
    int i = 0;
    unsigned int j = 0;
    long int k = 0;
    int *l;
    uint64_t m = 0;

    printf("isize of int %d size of long %d size of uint %d unsigned long long %d\n",sizeof(i), sizeof(k), sizeof(j), sizeof(m));
    printf("isize of int * %d \n", sizeof(int *));

    bit_manipulation();
}
int bit_manipulation(void)
{
    uint64_t hi_port_map [16] = {0, 2, 4, 6, 8, 10, 12, 14, 24, 26, 28, 30, 32, 34, 36, 38};
    uint64_t pmask = 0;
    int pstart = 0;
    int pend = 47;
    int i=0, j = 0;
    int portmask = 0xFFFF;
    uint64_t port = 0;
    pmask = 0xFFFF0000FFFF;
    port = ((uint64_t)1 << 33);
        printf("pmask=0x%llx bit=0x%llx\n", pmask, port);
        pmask = 0;
        for( i == 0; i < 16; i++) {
            if(portmask & (1 << i)) {
                port = ((uint64_t)1 << (uint64_t)hi_port_map[i]);
                pmask = pmask | port;
                printf("pmask=0x%llx bit=0x%llx\n", pmask, port);
            }
        }
        for(j=pstart; j <= pend; j++) {
            if(pmask & ((uint64_t)1 << (j - pstart))) {
                printf("setting lpbk for port %d pmask=0x%llx bit=0x%llx \n", j, pmask, ((uint64_t)1 << (j - pstart)));
            }
        }
}
