
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#define MAP_SIZE 1024

int main(void)
{
    int rc;
    int nvram_size = MAP_SIZE;
    int test = (nvram_size/1024);
    char syscmd[50];

    sprintf(syscmd, "dd if=/dev/urandom bs=1K count=%d of=./nvram.data", test);
      rc = system(syscmd);
              printf("Created random data file /nvram.data size %dKB  rc = %d -> %d\n", nvram_size/1024, rc, WEXITSTATUS(rc));
    sprintf(syscmd, "dd if=/dev/zero bs=1K count=%d of=./nvram.copy", test);
      rc = system(syscmd);
              printf("Created zero file /nvram.copy size %dKB rc = %d -> %d\n", nvram_size/1024, rc, WEXITSTATUS(rc));
    return rc;
}
