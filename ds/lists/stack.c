/*
 * gcc.c4.2.1-p4a.x86_64 -g3 stack.c -o stack
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
/* We use link list to pull and push data*/
int push_on_to_stack(struct node *node, char *str)
{
    struct node *tmp=NULL;
    if(node == NULL)  {
        node = (struct node *)malloc(sizeof(struct node ));
        node->next = NULL;
        strcpy(node->str, str);
        return 0;
    }
    tmp = node;
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
int pop_from_stack(struct node *node, char *str)
{
    struct node *tmp = NULL;
    if(node == NULL)
        return 0;
    tmp = node->next;
    if(tmp != NULL) {
        node->next = tmp->next;
        strcpy(str, tmp->str);
        free(tmp);
    }
    return 0;
}
int main()
{
    unsigned int val = 0;
    char str[50];
    struct node root ;
    char str1[50];
    push_on_to_stack(&root, "one");
    push_on_to_stack(&root, "two");
    push_on_to_stack(&root, "three");
    pop_from_stack(&root, str1);
    printf(" string:%s\n", str1);
    pop_from_stack(&root, str1);
    printf(" string:%s\n", str1);
    pop_from_stack(&root, str1);
    printf(" string:%s\n", str1);


    printf("val=%d string:%s\n", val, str); 
    return 0;
}
