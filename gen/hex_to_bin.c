#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void hex_to_bin(unsigned int num, char *str)
{
    char tmp[64];
    tmp[0] = '\0';
    unsigned int val = 0;
    int i = 0;
    while(num) {
        if(num & 1) {
            sprintf(str, "%d%s", 1, tmp);
        }else
            sprintf(str, "%d%s", 0, tmp);
            strcpy(tmp, str);
            num >>= 1;
        i++;
    }
}
int main(void)
{
    char str[64];
    int num = 0xa5a;
    hex_to_bin(num, str);
    printf("num=%x str=0x%s\n",num,str);

}
