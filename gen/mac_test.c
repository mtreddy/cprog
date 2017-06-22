#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    FILE *file;
    char str[50];
    char str1[50];
    char delim[] = "         ";
    char *ptr = NULL;
    int res = 0;
    file = fopen("./mac_test.txt", "r");
    while(!feof(file)) {
        fgets(str, 100, file);
        strcpy(str1, str);
        ptr = strstr(str, "Register test");
        if(ptr != NULL) {
            if(ptr) ptr = strtok(str1, delim);
            strcpy(str, ptr);
            if(ptr) ptr = strtok(NULL, delim);
            if(ptr) ptr = strtok(NULL, delim);
            if(ptr) ptr = strtok(NULL, delim);
            res = strtoul(ptr, NULL, 0);
            if(res)
                printf("%s Test failed %d times \n", str, res);
        }
        ptr = strstr(str, "Eeprom test");
        if(ptr != NULL) {
            if(ptr) ptr = strtok(str1, delim);
            strcpy(str, ptr);
            if(ptr) ptr = strtok(NULL, delim);
            if(ptr) ptr = strtok(NULL, delim);
            if(ptr) ptr = strtok(NULL, delim);
            res = strtoul(ptr, NULL, 0);
            if(res)
                printf("%s Test failed %d times \n", str, res);
        }
        ptr = strstr(str, "Interrupt test");
        if(ptr != NULL) {
            if(ptr) ptr = strtok(str1, delim);
            strcpy(str, ptr);
            if(ptr) ptr = strtok(NULL, delim);
            if(ptr) ptr = strtok(NULL, delim);
            if(ptr) ptr = strtok(NULL, delim);
            res = strtoul(ptr, NULL, 0);
            if(res)
                printf("%s Test failed %d times \n", str, res);
        }
        ptr = strstr(str, "Loopback test");
        if(ptr != NULL) {
            if(ptr) ptr = strtok(str1, delim);
            strcpy(str, ptr);
            if(ptr) ptr = strtok(NULL, delim);
            if(ptr) ptr = strtok(NULL, delim);
            if(ptr) ptr = strtok(NULL, delim);
            res = strtoul(ptr, NULL, 0);
            if(res)
                printf("%s Test failed %d times \n", str, res);
        }
        ptr = strstr(str, "Link test");
        if(ptr != NULL) {
            if(ptr) ptr = strtok(str1, delim);
            strcpy(str, ptr);
            if(ptr) ptr = strtok(NULL, delim);
            if(ptr) ptr = strtok(NULL, delim);
            if(ptr) ptr = strtok(NULL, delim);
            res = strtoul(ptr, NULL, 0);
            if(res)
                printf("%s Test failed %d times \n", str, res);
        }
    }
}
