#include <stdio.h>
#include <fcntl.h>
#define FILEPERM        (S_IRUSR|S_IWUSR)
#define ALL_FILEPERM (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) 
int main(int argc, char** argv)
{
    int fdr, fdw;
    char buff1[100] = "This file was created\n";
    char buff[256];
    int rc = 0;
    int n = 0;


    if(argc < 2) {
        printf("Syntax: ./file_rw <file-name>\n");
        printf("Creating test.txt file\n");
        fdr = creat("test.txt",ALL_FILEPERM);
        n = write(fdr, buff1, sizeof(buff1));
        if(n <= 0) {
            printf("Could not write to file test.txt\n"); 
            return -1;
        }
        close(fdr);
        fdr = open("test.txt", O_RDWR, FILEPERM);
        if(fdr <= 0) {
            printf("Could not open  file test.txt\n"); 
            return -1;
        }

    } else {
        if (access(argv[1], R_OK) < 0)
            printf("access error for %s\n", argv[1]);
        else
            printf("read access OK\n");
        fdr = open(argv[1], O_RDWR, FILEPERM);
        if(fdr <= 0) {
            printf("Failed to open the file.\n"
                    "So creating new file test.txt\n");
            fdr = creat("test.txt",FILEPERM);
            n = write(fdr, buff1, sizeof(buff1));
        }
    }

    fdw = creat("test_wr.txt",  ALL_FILEPERM);
    if(fdw <= 0) {
        printf("Failed to create file to write\n");
        return -1;
    }

    while((n = read(fdr, buff, sizeof(buff))) > 0) {
        rc = write(fdw, buff, n);
        if(rc != 0)
            continue;
        else
            printf("Data not avaialble to write to file\n");

    }

    close(fdw);
    close(fdr);
    return 0;
}
