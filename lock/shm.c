#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    const char shmem[] = "/shm_open";
    int fd = shm_open(shmem, O_CREAT| O_RDWR, 0666);
    if(fd == -1)
        printf("failed to open..\n");
    else
        printf("Success..\n");

    return;
}
