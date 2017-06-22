#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>

int main(int argc, char** argv)
{
    char fname[20] = "./rand_wr.fio";
    FILE *fd;
    char str[50];
    char str1[50];
    char *ptr;

    fd = fopen(fname, "a+");

    while(!feof(fd)){
        fgets(str, 50, fd);
        ptr = strstr(str,"size");
        if(ptr != NULL) {
            strcpy(str1, ptr);
            printf("Found it\n");
            fputs("directory=/mnt_usb_bw\n", fd);
            break;
        }
    }
    fclose(fd);
}
