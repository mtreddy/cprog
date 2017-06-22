#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>

#define mb_size (2*1024*1024)

typedef unsigned int uint32;
typedef unsigned long long  uint64;

int main(int argc, char **argv)
{


    char src[25] = "nvram.data";
    char dst[25] = "nvram.copy";
    void *saddr, *daddr;


    int src1, dst1;

    src1 = open(src, O_RDONLY);
    if(src1 <= 0 ) {
        printf("Cound not open file %s\n", src);
        return -1;
    }
    saddr = mmap(0, mb_size, PROT_READ , MAP_SHARED, src1, 0);
    if(saddr == -1 ) {
        printf("Cound not mmap file %s\n", src);
        return -1;
    }
    dst1 = open(dst, O_RDONLY);
    if(dst1 <= 0 ) {
        printf("Cound not open file %s\n", dst);
        return -1;
    }
    daddr = mmap(0, mb_size, PROT_READ , MAP_SHARED, dst1, 0);
    if(daddr == -1  ) {
        printf("Cound not mmap file %s\n", dst);
        return -1;
    }

    uint64 *copy = saddr, *data = daddr;
    int errors = 0;
    while(((uint32)copy - (uint32)data) < mb_size) {
        if(*(data++) != *(copy++)) {
            errors++;
            if(errors < 10) {
                printf("Data missmatch expected 0x%x(addr=0x%llx) got=0x%x(addr=0x%llx)\n", *data, data, *copy, copy);
            }
    
        }
    }

    munmap(saddr, mb_size);
    munmap(daddr, mb_size);
    close(src1);
    close(dst1);
}
