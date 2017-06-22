/*
 * gcc.c4.2.1-p4a.x86_64 -g3 btree_to_dlisto_dlist
 */
/*
 The idea can be described using below steps.
    1) Write a general purpose function that concatenates two given circular doubly lists (This function is explained below).
    2) Now traverse the given tree
    ….a) Recursively convert left subtree to a circular DLL. Let the converted list be leftList.
    ….a) Recursively convert right subtree to a circular DLL. Let the converted list be rightList.
    ….c) Make a circular linked list of root of the tree, make left and right of root to point to itself.
    ….d) Concatenate leftList with list of single root node.
    ….e) Concatenate the list produced in step above (d) with rightList.

    Note that the above code traverses tree in Postorder fashion. We can traverse in inorder fashion also. We can first concatenate left subtree and root, then recur for right subtree and concatenate the result with left-root concatenation. 
 */
#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node *left, *right;
    int val;
};
struct node* btree_create_node(int data)
{
    struct node *node;
    node = (struct node *)malloc(sizeof(struct node));
    node->left =  NULL;
    node->right = NULL;
    node->val = data;
    printf("Create %d val=%d\n", __LINE__, data);
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
                printf("Line  %d going left root val %d \n", __LINE__, tmp->val);
                btree_insert(&tmp, val);
            } else {
                printf("Line  %d going left root val %d \n", __LINE__, tmp->val);
                btree_insert(&tmp->left, val);
            }
        } else {
            if(tmp->right != NULL) {
                tmp = tmp->right;
                btree_insert(&tmp, val);
                printf("Line  %d going Right root val %d \n", __LINE__, tmp->val);
            } else {
                btree_insert(&tmp->right, val);
                printf("Line  %d going Right root val %d \n", __LINE__, tmp->val);
            }
        }
    }
}
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
struct node * get_next_node(struct node **root)
{
    struct node *tmp;
    tmp = *root;
    if(tmp == NULL)
        return NULL;
    if(tmp->left != NULL) {
        get_next_node(&tmp->left);
    } else {
        printf("left val=%d\n", tmp->val);
    }
    if(tmp->right != NULL) {
        get_next_node(&tmp->right);
    } else {
        printf("right val=%d\n", tmp->val);
    }
}
int contatante_two_nodes( struct node *left, struct node *right)
{
}
int convert_btree_to_clist(struct node *root)
{
}

int main(void)
{
    /* Build binary tree*/
    struct node* root = NULL;
    root =  btree_create_node(25);
    btree_insert(&root, 12);
    btree_insert(&root, 13);
    btree_insert(&root, 11);
    btree_insert(&root, 29);
    btree_insert(&root, 9);
    btree_insert(&root, 50);
    btree_insert(&root, 14);
    btree_print(root);
    get_next_node(&root);
}
