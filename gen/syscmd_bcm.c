//gcc.c4.2.1-p4.x86_64   syscmd_bcm.c  -o syscmd_bcm
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

    sprintf(syscmd, "/lc/isan/bcm/bcm-shell *: soc", test);
      rc = system(syscmd);
              printf(" bcm-shel command finished  rc = %d -> %d\n", nvram_size/1024, rc, WEXITSTATUS(rc));
    return rc;
}
