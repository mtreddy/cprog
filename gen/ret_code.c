#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
    int rc;


   // rc = system("lspci -v | grep 82545EM");
    //printf("rc = %d -> %d\n", rc, WEXITSTATUS(rc));
    //rc = system("cat /proc/cpuinfo | grep -v bogomips | grep -v MHz | md5sum | grep 23418f0847dffe155789b49a5d42bee0");
    rc = system("diff /nvram.data /nvram.copy");
    if(rc != 0) printf("Files are not same");
    else printf("Files are  same");
    printf("\n rc = %d -> %d\n", rc, WEXITSTATUS(rc));
    return (rc == 0) ? 0: -1;
    //return 0;
}
