/*
 * Copy right 2024
 */
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    FILE* file;
    char str[100];
    char dstr[100];
    char *ptr;


    file = fopen("./cpu_info.txt", "r");
    if(file == NULL) {
        printf("Could not open file ...!!\n");
        return -1;
    }

    while(!feof(file)) {
        fgets(str, 100, file);
        ptr = strstr(str, "Intel");
        if(ptr) {
            ptr = strstr(str, "Core");
            if(ptr) {
                printf("CPU:%s", ptr);
                strncpy(dstr,ptr,strlen(ptr) - 1);
            }
        }
    }

    printf("CPU string:%s is here\n", dstr);
}
