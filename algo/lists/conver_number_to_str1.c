/*
 * gcc.c4.2.1-p4a.x86_64 -g3 conver_number_to_str1.c  -o conv
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int num_str(int num, char *str)
{
    char tmp1[50], tmpt[50], tmp10[50], tmp100[50], tmp1000[50];
    int tmp = 0;
    char *ones[] = {"NA", "one", "two", "three", "four", "five", "six", "seven", "eight", "Nine"};
    char *teens[] = {"ten", "eleven", "tweleve", "thirteen", "fourteen", "fifteen", "sixtenn", "seventeen", "eighteen", "ninteen"};
    char *tens[] = {"NA", "twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninty" };
   tmp = num % 10;
   if(tmp != 0) {
       if(num/10 == 1) {
            strcpy(tmp1, teens[tmp]);
       } else { 
            strcpy(tmp1, ones[tmp]);
       }
   }
   tmp = num/10;
   if(tmp > 1)
       strcpy(tmp10, tens[tmp - 1]);
   sprintf(str, "%s %s", tmp10, tmp1);
}
int main(void)
{
    char str[100];

    num_str(24,str);
    printf("%s\n", str);
}
