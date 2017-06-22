#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main () {
    int rc = 0;
        rc = system("/isan/bin/vsh -nRc \"slot 1 quoted \"sh hardware internal bcm event sdk\" > bootflash:test.log\""); 
        printf("rc = %d -> %d\n", rc, WEXITSTATUS(rc)); 
        rc = system("/isan/bin/vsh -nRc \"slot 1 quoted \\\"sh hardware internal bcm event sdk\\\" > bootflash:test.log\""); 
        printf("rc = %d -> %d\n", rc, WEXITSTATUS(rc)); 

        return 0;
}
