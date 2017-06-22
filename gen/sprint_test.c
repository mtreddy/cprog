#include <stdio.h>
#include <string.h>

int main(void)
{
    int flen = 5;
    char str[10] = "0102030405";
    char tstr[10];
    char tmp[10];
    char tchar;
    int i = 0;

    for(i = 0; i< 8; i++) {
        tchar = str[i];
        sprintf(tstr, "%s%c", tmp, tchar);
        strcpy(tmp, tstr);
    }

    printf("tmp %s\n", tmp);
    printf("209 ascci %d\n", 'c');
    printf("209 ascci %c\n", 99);
}
