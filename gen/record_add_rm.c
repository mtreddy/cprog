#include <stdio.h>
#include <fcntl.h>
//#include <unstd.h>

#define FILEPERM        (S_IRUSR|S_IWUSR)
#define ALL_FILEPERM (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) 

int main(void)
{
    char fname[] = "./record.csv";
    int fd = 0;
    char str[250];
    int i = 0;
#if 0
    if((fd = open(fname, O_RDWR, FILEPERM)) < 0) {
        printf("Failed to open the file. Going to create the file\n");
        if((fd = creat(fname, ALL_FILEPERM)) < 0) {
            printf("Failed to create the file. Going to create the file\n");
            return -1;
        }
    
        if((fd = open(fname, O_RDWR, FILEPERM)) < 0) {
            printf("Failed to open the file. Even after creating it \n");
            return -1;
        }
    }

    for( i = 0; i < 10; i++) {
        sprintf(str, "%s%d, %d ", "do something\n", i, i);
        write(fd, str, 250);
    }

    close(fd);
#else
    FILE *fw;

    fw = fopen(fname,  "a+b");
    if(fw == NULL) {
        printf("Failed to open the file\n");
        return -1;
    }
    for( i = 0; i < 10; i++) {
        sprintf(str, "%s%d, %d \n", "do something", i, i);
        fprintf(fw, str);
    }

    fclose(fw);
#endif

}
