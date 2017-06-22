#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char** argv)
{
    char str1[100];
    char *str = "m=audio 49462 RTP/AVP 0 8";
    char *element= "m=audio 49462 RTP/AVP 0 8";
    int val = 0, val1=0;
    strcpy(str1, argv[1]);
    printf("string is %s\n", argv[1]);
    sscanf(argv[1], "%*s %d", &val);
    printf("val is %d\n", val);
    sscanf(str1, "%*s Address %d %*s", &val);
    printf("val is %d \n", val);
    val1 = 0;
    sscanf(str, "%*s %d", &val1);
    printf("val1 %d\n", val);
    return 0;
}
