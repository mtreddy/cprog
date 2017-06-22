#include <stdio.h>
#include <stdlib.h>
typedef unsigned char uint8;
typedef unsigned int uint32;
int main(int argc, char **argv)
{
    int i = 0;
    uint8   *data_buf;
    data_buf = (uint8 *)malloc(sizeof(uint32) * 0x40000);
    if (data_buf == NULL) {
        printf("Failed to allocate memory for data back buffer!\n");
    }
    for(i = 0; i < 100; i+=4) {
            *(uint32 *)(data_buf + i ) = rand();
            printf("data_buf = 0x%x *data_buf = 0x%x\n", data_buf + i, *(uint32 *)(data_buf + i));

    }

    free(data_buf);
}

