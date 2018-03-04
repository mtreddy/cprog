/*
 * gcc.c4.2.1-p4a.x86_64 -g3 conver_number_to_str.c  -o conv
 */
#include<stdio.h>
#include<string.h>
#include<inttypes.h>
#include<stdlib.h>
struct node {
    struct node *next;
    struct node *prev;
    char str[50];
}node_t;
int conv_10_19(int num, char *str) {
    switch(num) {
        case 10:
            strcpy(str,"ten");
            break;
        case 11:
            strcpy(str,"Eleven");
            break;
        case 12:
            strcpy(str,"twelve");
            break;
        case 13:
            strcpy(str,"thirteen");
            break;
        case 14:
            strcpy(str,"fourteen");
            break;
        case 15:
            strcpy(str,"fifteen");
            break;
        case 16:
            strcpy(str,"sixteen");
            break;
        case 17:
            strcpy(str,"seventeen");
            break;
        case 18:
            strcpy(str,"Eighteen");
            break;
        case 19:
            strcpy(str,"Ninteen");
            break;
        default:
        printf("Error: Invalid number%d", num);
    }
    return 0;
}
int conv_10s(int num, char *str)
{
    switch(num) {
        case 20 ... 29:
            strcpy(str, "twenty");
            break;
        case 30 ... 39:
            strcpy(str, "Thirty");
            break;
        case 40 ... 49:
            strcpy(str, "Fourty");
            break;
        case 50 ... 59:
            strcpy(str, "Fifty");
            break;
        case 60 ... 69:
            strcpy(str, "Sixty");
            break;
        case 70 ... 79:
            strcpy(str, "Seventy");
            break;
        case 80 ... 89:
            strcpy(str, "Eighty");
            break;
        case 90 ... 99:
            strcpy(str, "Ninty");
            break;
        default:
            printf(" Not implemetned yet");
    }

    return 0;
}
int conv_1s(int num, char *str)
{
    switch(num){
        case 1:
            strcpy(str, "one");
            break;
        case 2:
            strcpy(str, "two");
            break;
        case 3:
            strcpy(str, "three");
            break;
        case 4:
            strcpy(str, "four");
            break;
        case 5:
            strcpy(str, "five");
            break;
        case 6:
            strcpy(str, "six");
            break;
        case 7:
            strcpy(str, "seven");
            break;
        case 8:
            strcpy(str, "eight");
            break;
        case 9:
            strcpy(str, "Nine");
            break;
        default:
            strcpy(str, "NULL");
    }
    return 0;
}
int one_hundread(int num, char *str) {
    char str1[25];
    int tmp, tmp1;
    /*get rid of digits below 100*/
    tmp = num%1000 - num%100;
    //printf("line:%d tmp=%d\n", __LINE__, tmp);
    tmp = tmp/100;
    if(tmp != 0) {
        conv_1s(tmp,str1);
        sprintf(str1, "%s %s", str1, "Hundread");
        strcpy(str, str1);
        //printf("line:%d str=%s\n", __LINE__, str);
    }
    return;
}
int one_thousand(int num, char *str) {
    char str1[30], str2[30], str3[30], str4[50];
    int tmp, tmp1;
    /*get rid of digits below 1000 */
    tmp = num%1000000 - num%1000;
    //printf(" %s num=%d tmp=%d\n", __func__, num, tmp);
    tmp = tmp/1000;
    if(tmp != 0) {
        tmp1 = tmp%100;
        printf("tmp1=%d tmp=%d line=%d\n", tmp1, tmp, __LINE__);
        if((tmp1 >=10) && (tmp1 < 20)) {
            conv_10_19(tmp1, str1);
        } else {
            tmp1 = tmp%100 - tmp%10;
            //printf("tmp1=%d line=%d\n", tmp1, __LINE__);
            conv_10s(tmp/10,str2);
            tmp1 = tmp%10;
            conv_1s(tmp,str1);
        }
        if (tmp%100) {
            //printf("tmp1=%d line=%d\n", tmp1, __LINE__);
            one_hundread(tmp1, str3);
        }
        sprintf(str4, "%s %s %s %s", str3, str2, str1, "Thousand");
        //printf("%s %s\n", __func__, str4);
        strcpy(str, str4);
    }
    return;
}
int conv_100s(int num, char *str){
    char str1[10],str2[10],str3[25],str4[50];
    int tmp = 0;
    //printf("line=%d num/100=%d num/1000=%d\n", __LINE__, num/100, num/1000);
    if(num/100) {
        one_hundread(num, str1);
    }
    if(num/1000) {
        one_thousand(num, str2);
    }
        sprintf(str4, " %s %s", str2, str1);
        //printf("%s %s\n", __func__, str);
        strcpy(str, str4);
}
/* We use link list to pull and push data*/
int push_on_to_stack(struct node **node, char *str)
{
    struct node *tmp=NULL;
    if(*node == NULL)  {
        *node = (struct node *)malloc(sizeof(struct node ));
        (*node)->next = NULL;
        strcpy((*node)->str, str);
        return 0;
    }
    tmp = *node;
    while(tmp) {
        if(tmp->next == NULL) {
            tmp->next = (struct node *) malloc(sizeof(struct node));
            strcpy(tmp->next->str, str);
            tmp->next->next = NULL;
            break;

        }
        tmp = tmp->next;
    }
    return 0;
}
int pop_from_stack(struct node **node, char *str)
{
    struct node *tmp = NULL;
    if(*node == NULL) {
        printf("Stack is empty..!!\n");
        return 0;
    }
    tmp = *node;
    if(tmp != NULL) {
        *node = tmp->next;
        strcpy(str, tmp->str);
        free(tmp);
    }
    return 0;
}
/* Convert number to a string */
int main(int argc, char **argv)
{
    unsigned int val = 0;
    char str1[50];
    char str[100];
    struct node *root=NULL;
    int push_cnt = 0;

    if(argc < 2) {
        printf("Syntax: ./conver_number_str <number>\n");
        return 0;
    }
    printf("argc=%d argv[1]=%s\n", argc, argv[1]);
    val = strtol(argv[1], (char *)NULL, 10);
    //printf("val = %d\n",val);
    int tmp = val % 100;
    /* get string up to trillion*/
    if(val > 100) {
        conv_100s(val, str);
        //printf("val=%d string:%s\n", val, str);
        push_on_to_stack(&root, str);
        push_cnt++;
    }
    if( val%100) {
        tmp = val % 100;
        if((tmp >=10) && (tmp < 20)) {
            conv_10_19(tmp, str);
            //printf("val=%d string:%s\n", val, str);
            push_on_to_stack(&root, str);
            push_cnt++;
        } else {
            /*get rid of ones digit*/
            tmp = val%100 - val%10;
            if(tmp/10) {
                conv_10s(tmp, str);
                //printf("val=%d string:%s\n", val, str);
                push_on_to_stack(&root, str);
                push_cnt++;
            }
            /*Get ones digit */
            tmp = val%10;
            if(tmp) {
                conv_1s(tmp, str);
                //printf("val=%d string:%s\n", val, str);
                push_on_to_stack(&root, str);
                push_cnt++;
            }
        }
    }
    while(push_cnt--) {
        pop_from_stack(&root, str1);
        printf("%s ", str1);
    }
    printf("\n");
        
}

