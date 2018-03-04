/*
 * gcc.c4.2.1-p4a.x86_64 -g3 btree_1.c  -o btree_1
 */
#include <stdio.h>
#include <string.h>
#include <malloc.h>


struct node {
    struct node* left;
    struct node* right;
    int val;
}node_t;

struct node* btree_create_node(int data)
{
    struct node *node;
    node = (struct node *)malloc(sizeof(struct node));
    node->left =  NULL;
    node->right = NULL;
    node->val = data;
    //printf("Create %d val=%d\n", __LINE__, data);
    return node;
}
void btree_insert(struct node** node, int val)
{
    struct node  *tmp;
    if( *node == NULL ) {
        *node = btree_create_node(val);
        return;
    } else {
        tmp = *node;
        if(val <= tmp->val )  {
            if(tmp->left != NULL) {
                tmp = tmp->left;
                //printf("Line  %d going left root val %d \n", __LINE__, tmp->val);
                btree_insert(&tmp, val);
            } else {
                //printf("Line  %d going left root val %d \n", __LINE__, tmp->val);
                btree_insert(&tmp->left, val);
            }
        } else {
            if(tmp->right != NULL) {
                tmp = tmp->right;
                btree_insert(&tmp, val);
                //printf("Line  %d going Right root val %d \n", __LINE__, tmp->val);
            } else {
                btree_insert(&tmp->right, val);
                //printf("Line  %d going Right root val %d \n", __LINE__, tmp->val);
            }
        }
    }
}
void btree_print(struct node *node);

void btree_print(struct node *node)
{
    struct node* tmp;
    tmp = node;
   if (tmp != NULL) {
            btree_print(tmp->left);
            printf("data=%d\n", tmp->val);
            btree_print(tmp->right);
    }
}
struct node *get_min(struct node *node)
{
    struct node *tmp;
    tmp = node;
    while(tmp->left){
        tmp = tmp->left;
    }
    return tmp;
}
struct node *get_max(struct node *node)
{
    struct node *tmp;
    tmp = node;
    while(tmp->right){
        tmp = tmp->right;
    }
    return tmp;
}
struct node* get_succesor(struct node* node, int val)
{
    struct node *tmp;
    if(node == NULL)
        return node;
    tmp = node;
    /*If there is min on right of the root that would be your successor*/
    if(( tmp->left && (tmp->left->val == val)) ) {
            return (tmp);
    }
     if(( tmp->right && (tmp->right->val == val))) {
            return get_min(tmp);
     }

    if(node->val > val)
        return get_succesor(node->left, val);
    else
        return get_succesor(node->right, val);
}
void get_predessor(struct node* node, struct node **pre, int val)
{
    struct node *tmp;
    if(node == NULL)
        return ;
    tmp = node;
    /* if thre is right get max of right*/
    if(tmp->val == val) {
        if(tmp->left) {
            return get_max(tmp->left);
        }
    }
    if(node->val > val)
        return get_predessor(node->left, val);
    else
        return get_predessor(node->right, val);
}

int main(void)
{
    struct node* root = NULL;
    struct node* tmp = NULL;
    root =  btree_create_node(31);
    btree_insert(&root, 14);
    btree_insert(&root, 9);
    btree_insert(&root, 19);
    btree_insert(&root, 5);
    btree_insert(&root, 11);
    btree_insert(&root, 15);
    btree_insert(&root, 23);
    btree_insert(&root, 1);
    btree_insert(&root, 7);
    btree_insert(&root, 10);
    btree_insert(&root, 13);
    btree_insert(&root, 39);
    btree_insert(&root, 35);
    btree_insert(&root, 49);
    btree_insert(&root, 33);
    btree_insert(&root, 37);
    btree_insert(&root, 43);
    btree_insert(&root, 55);
    btree_insert(&root, 41);
    btree_insert(&root, 45);
    btree_insert(&root, 52);
    btree_insert(&root, 62);
    btree_print(root);
    tmp =  get_max(root);
    printf("max is %d\n", tmp->val);
    tmp =  get_min(root);
    printf("min is %d\n", tmp->val);
    tmp = get_predessor(root, 41);
    if(tmp)
        printf("predessor %d\n", tmp->val);
    else
        printf("predessor not found\n");
    tmp = get_succesor(root, 45);
    if(tmp)
        printf("successor %d\n", tmp->val);
    else
        printf("successor not found\n");
    return 0;
}

