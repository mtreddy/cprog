#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (char main)
{
    FILE* file;
    char disk_name[20] = "/dev/sdb";
    char str[100];
    char str1[100];
    char *ptr, *pch;
    char delim[] = " =,";
    char hdpar[25]; 
    //system("rm hdparm.txt");
    //sprintf(hdpar, "hdparm %s > hdparm.txt", disk_name); 

    file = fopen("hdparm.txt", "r");
    if(file == NULL)
        return -1;
    while(!feof(file)) {
        fgets(str, 100, file);
        pch = strstr(str, "sectors");

        if(pch != NULL) {
            strcpy(str1, pch);
            ptr = strtok(str1,delim);
            if(ptr == NULL)
                break;
            ptr = strtok(NULL,delim);
            if(ptr == NULL)
                break;

            int sectors = strtoul(ptr,NULL,0);
            if(sectors == 0)
                printf("Number of sectros is zero which is not right\n");
            else
                printf("sectors %d \n", sectors);
            //ptr = strtok(NULL,delim);
            //if(ptr != NULL)
             //   printf("%s\n", ptr);

            break;
        }
    }
    fclose(file);
    return sectors;
    
}
