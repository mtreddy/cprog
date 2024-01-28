#include<stdio.h>
#include<malloc.h>
/*
 * iImplement a function to reverse a linked list, and return the head of the reversed list. A list node is defined as below:
 */
struct node{
    int       val;
    struct node* next;
};

int list_add_node(struct node **root, int val)
{
    struct node *tmp;
    if(*root == NULL) {
        *root = (struct node *)malloc(sizeof(struct node));
        (*root)->val = val;
        (*root)->next = NULL;
        return 0;
    }
    tmp = *root;
    while(tmp->next) {
        //printf("val=%d\n",tmp->val);
        tmp = tmp->next;
    }
    if(!tmp->next) {
        tmp->next = (struct node *)malloc(sizeof(struct node));
        tmp->next->val = val;
        tmp->next->next = NULL;
        return 0;
    }
    return 0;
    
}
int list_push_node(struct node **root, int val)
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->val = val;
    temp->next = (*root);
    (*root) = temp;
}
void list_reverse(struct node **root)
{
    struct node *prev = NULL;
    struct node *curr = (*root);
    struct node *next = NULL;
    while(curr!=NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    (*root) = prev;
}
void list_print(struct node *root)
{
    struct node *tmp = NULL;
    tmp = root;
    printf("Printing list....\n");
    while(tmp->next) {
        printf("val=%d\n",tmp->val);
        tmp = tmp->next;
    }
}

int main()
{
    struct node *root;

    list_add_node(&root,10);
    list_add_node(&root,100);
    list_add_node(&root,20);
    list_print(root);
    list_push_node(&root, 40);
    list_print(root);
    list_reverse(&root);
    list_print(root);
}




