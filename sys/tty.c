#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int main()
{
    char term[] = "/dev/pts/16";

    int fd  = 0;


    fd = open(term, O_RDWR | O_NONBLOCK);

    write(fd,"ls\n", 5);
}
