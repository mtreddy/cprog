#include<stdio.h>
#include "hash.h"


uint32  hashpjw(const void *key)
{
    const char *ptr;
    uint32 val = 0;
    ptr = key;
    while(*ptr != '\0'){
        uint32 tmp = 0;
        val = (val << 4) + (*ptr);
        if (tmp = (val & 0xf0000000)){
            val = val ^(tmp >> 24);
            val = val ^ tmp;
        }
        ptr++;
    }
    return val % PRIME_TBLSZ;
}

int main()
{
    printf("key = 0x%x\n", hashpjw("abrakadabbar"));
    printf("key = 0x%x\n", hashpjw("12345678"));
}
