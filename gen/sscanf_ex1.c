#include<stdio.h>

int main()
{
    char *element= "m=audio 49462 RTP/AVP 0 8";

    int num;
    sscanf(element, "%*s %d", &num);

    printf("%d\n",num);
    return 0;
}
