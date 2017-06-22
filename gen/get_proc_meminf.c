#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{
    int rc = 0;
    FILE *file = NULL;
    char str[100];
    char str1[100];
    char *ptr = NULL;
    int found_str = 0;
    int mem_free = 0;


    rc = system("cat /proc/meminfo > /tmp/meminfo.txt");

    file = fopen("/tmp/meminfo.txt", "r");
    if(file == NULL) { 
        printf("Failed to open file %s\n", "/tmp/meminfo.txt");
        return -1;
    }

    while(!feof(file)) {
        fgets(str, 100, file);
        ptr = strstr(str, "MemFree:");
        if(ptr!= NULL) {
            found_str = 1;
            strcpy(str1, str);
            ptr = strtok(str, ":");
            if(ptr != NULL)
                printf("%s\n", ptr);
            ptr = strtok(NULL, ":");
            if(ptr != NULL)
                printf("%s\n", ptr);
            mem_free = strtoul(ptr, NULL, 0);
            printf("Free mem is %d\n", mem_free);
            if(mem_free > 0x20000)
                mem_free -= 0x10000;
            else if (mem_free > 0x10000)
                mem_free -= 0x08000;
            else if (mem_free > 0x08000)
                mem_free -= 0x04000;
            else if (mem_free > 0x04000)
                mem_free -= 0x02000;
            else if (mem_free > 0x02000)
                mem_free -= 0x01000;
            else if (mem_free > 0x01000)
                mem_free -= 0x00800;
            else {
                printf("ERROR:Not enough free memoyr..!!\n");
                rc = -1;
            }
            printf("Free mem size that can be tested is %d\n", mem_free);
        }
    }
    if(found_str)
        printf("Found string\n");
    else {
        printf("Did not found string\n");
        rc = -1;
    }

    fclose(file);
    rc = system("rm /tmp/meminfo.txt");
    return rc;
}
