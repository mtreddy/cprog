#include <stdio.h>
#include <string.h>
#include <stddef.h>

int main()
{
    char str[] = "  dir: /sys/bus/scsi/devices/6:0:0:0  [/sys/devices/pci0000:00/0000:00:1d.0/usb1/1-1/1-1.6/1-1.6:1.0/host6/target6:0:0/6:0:0:0]";
    //char str[100] = "dir:/sys/bus/scsi/devices/usb1/6:0:0:0";
    char *pch, *ptr, buf[100], str1[100];
    char delim[] = "/";

    ptr = strstr(str, "usb1");
    strcpy(buf, ptr);
    strcpy(str1, ptr);
    printf("buf: %s\n", buf);
    printf("str1: %s\n", buf);

    pch = strtok(buf, delim);
    //if(pch != NULL)
      //  printf("%s\n", pch);

    while(pch != NULL) {
        printf("%s\n", pch);
        pch = strtok(NULL, delim);
    }
}
