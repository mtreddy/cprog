#include <sys/mman.h>
#include <fcntl.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#define MAP_SIZE (1024 * 1024)
#define MAP_MASK (1024 * 1024)-1
int main(void)
{
    off_t          dev_base = 0x383ff8000000;
    size_t         ldev = (1024 * 1024);
    unsigned long  mask = (1024 * 1024)-1;
    int           *pu;
    void          *mapped_base;
    void          *mapped_dev_base;
    int  volatile *pcid;
    int  volatile  cid;
    int            memfd;

    memfd = open("/dev/mem", O_RDWR | O_SYNC);
    mapped_base = mmap(0, MAP_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, memfd, dev_base & ~MAP_MASK);
    if (mapped_base == MAP_FAILED)
        errx(1, "mmap failure");
    mapped_dev_base = mapped_base + (dev_base & MAP_MASK);
    pu = mapped_dev_base;

    pcid = (int *) (((void *) pu) + 0xf0704);

    //printf("pu    = %08p\n", pu);
    //printf("pcid  = %08p\n", pcid);

    //cid = *pcid;
    //printf("CID   = %x\n", cid);

    munmap(mapped_base, ldev);
    close(memfd);

    return (EXIT_SUCCESS);
}
