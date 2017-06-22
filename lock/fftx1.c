#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include "futextest.h"


#define timeout_ns 100000

int main(int argc, char  **argv[])
{
    struct timespec to = {.tv_sec = 0, .tv_nsec = timeout_ns};
    int ret = 0;
    futex_t f1 = FUTEX_INITIALIZER;
    to.tv_sec = 0;
    to.tv_nsec = timeout_ns;
    printf("Calling futex_wait on f1: %u @ %p with val=%u\n", f1, &f1, f1+1);

    
    ret = futex_wait(&f1, f1+1, &to, FUTEX_PRIVATE_FLAG);
    if(!ret || errno != EWOULDBLOCK) {
        printf("futex_wait returned %d\n", ret);
        return ret;
    }
    printf("futex_wait success %d errno %d\n", ret, errno);

    return ret;

}

