#include <stdio.h>

int main(int argc, char **argv)
{

    int port = strtoul(argv[1],NULL,0);
    int inst = 0;

    inst = port/4;

    port = port%4;

    printf("inst %d port %d\n", inst, port);
    
    return 0;
}
