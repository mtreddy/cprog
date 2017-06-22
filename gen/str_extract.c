#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main(void)
{
    char disk[25] = "/dev/sdb1";
    char *ptr = NULL;


    ptr = strtok(disk,"/");
    if(ptr!=NULL)
        printf("%s\n", ptr);
    else
        return;
    ptr = strtok(NULL,"/");
    if(ptr!=NULL)
        printf("%s\n", ptr);
    else
        return;
}
