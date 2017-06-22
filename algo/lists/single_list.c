/*
 * gcc.c4.2.1-p4a.x86_64 -g3 single_list.c  -o single_list
 */
#include<stdio.h>
#include<malloc.h>

typedef struct list{
    struct list *next;
    int data;
}list_t;
struct list * single_list_create_node(int data) {
    struct list *node ;

    node = (struct list *) malloc(sizeof(struct list));
    node->next = NULL;
    node->data = data;
    return node;
}
/*Delete node with data as arg*/
int single_list_delete_node(struct list **root, int data)
{
    struct list *tmp;
    struct list *tmp1;
    tmp = *root;
    /*If data matches first element*/ 
    if((*root)->data == data) {
        *root = tmp->next;
        free(tmp);
        return 0;
    }
    /* We deal with second element onwards here*/
    while(tmp->next) {
        if(tmp->next->data == data) {
            tmp1 = tmp->next;
            tmp->next = tmp->next->next;
            free(tmp1);
            return(0);
        }
        tmp = tmp->next;
    }
    printf("Could not find the element in thelist \n");
    return 1;
}
int single_list_print(struct list *node) {
    struct list *tmp = node;

    while(tmp) {
        printf("data=%d\n", tmp->data);
        tmp = tmp->next;
    }
}
int single_list_insert (struct list **node, int data){
    struct list *tmp = NULL;
    struct list *tmp1;
    if(*node == NULL) {
        *node = single_list_create_node(data);
        return 0;
    }
    /*Check if head need to be updated*/
    if(data > (*node)->data) {
        tmp = single_list_create_node(data);    
        tmp->next = *node;
        *node = tmp;
        printf("3 data=%d\n", data);
        return 0;
    }
    /*traverse list*/
    tmp = *node;
    while(tmp->next) {
        if(data > tmp->next->data) {
            tmp1 = single_list_create_node(data);
            tmp1->next = tmp->next;
            tmp->next = tmp1;
            printf("2 data=%d\n", data);
            return 0;
        }
        if(tmp->next)
            tmp = tmp->next;
    }
    printf("1 data=%d\n", data);
    tmp->next = single_list_create_node(data);
    return 0;
}
int main()
{
    struct list *root;
    /*
     *  Root
     */
    single_list_insert(&root, 1);
    /*
     * Add a member
     */
    single_list_insert(&root, 3);
    single_list_insert(&root, 12);
    single_list_insert(&root, 10);
    single_list_insert(&root, 17);
    single_list_insert(&root, 13);

    /*
     * Print
     */
    single_list_print(root);

    /*
     * Delete
     */
    single_list_delete_node(&root, 10);
    single_list_delete_node(&root, 11);

    /*
     * Print
     */
    single_list_print(root);
    /*
     * Add more nodes
     */
    single_list_insert(&root, 30);
    single_list_insert(&root, 29);
    /*
     * Print
     */
    single_list_print(root);
}
