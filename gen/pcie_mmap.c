#include <sys/mman.h>
#include <fcntl.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#define MAP_SIZE (1 * 1024 * 1024)
#define MAP_MASK (1 * 1024 * 1024)-1
int main(void)
{
    //off_t          dev_base = 0x383ff8000000;
    unsigned long long           dev_base = 0x383ff8000000;
    size_t         ldev = MAP_SIZE;
    unsigned long  mask = MAP_MASK;
    int           *pu;
    void          *mapped_base;
    void          *mapped_dev_base;
    int  volatile *pcid;
    int  volatile  cid;
    int            memfd;

    memfd = open("/dev/mem", O_RDWR | O_SYNC);
    mapped_base = mmap64(0, MAP_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, memfd, dev_base);
    printf("mapped_base = 0x%x\n", mapped_base);
    if (mapped_base == MAP_FAILED)
        errx(1, "mmap failure");
    mapped_dev_base = mapped_base + (dev_base & MAP_MASK);
    pu = mapped_dev_base;
    printf("mapped_dev_base = 0x%llx\n", (unsigned long long *)mapped_dev_base);
    pcid = (int *) (((void *) pu) + 0xf0704);

    //printf("pu    = %08p\n", pu);
    //printf("pcid  = %08p\n", pcid);

    //cid = *pcid;
    //printf("CID   = %x\n", cid);

    //munmap(mapped_base, ldev);
    while(1) {
        sleep(1);
    }
    close(memfd);

    return (EXIT_SUCCESS);
}
