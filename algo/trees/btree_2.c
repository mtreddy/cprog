#include <stdio.h>
#include <string.h>
#include <malloc.h>


struct btree{
    struct btree *left;
    struct btree *right;
    int val;
};

typedef struct btree node;
int insert(struct btree **tree, int val)
{
    struct btree *temp = NULL;

    if(*tree == NULL) {
        temp=(struct btree *)malloc(sizeof(struct btree));
        temp->left = temp->right = NULL;
        temp->val = val;
        *tree = temp;
        return;
    }

    if((*tree)->val > val) {
        insert(&(*tree)->right, val);
    } else {
        insert(&(*tree)->left, val);
    }
}

struct btree*  search(struct btree **btree, int val)
{

    if(*btree == NULL) 
        return NULL;

    if((*btree)->val == val)
        return *btree;
    else if((*btree)->val < val)
        search(&((*btree)->left), val);
    else
        search(&((*btree)->right), val);
    
}

void delete(node * tree)
{
    if(tree) {
        delete(tree->left);
        delete(tree->right);
        free(tree);
    }
}

void print_preorder(node * tree)
{
    if (tree) {
        printf("%d\n", tree->val);
        print_preorder(tree->left);
        print_preorder(tree->right);
    }
}

void print_postorder(node * tree)
{
    if (tree) {
        print_postorder(tree->left);
        print_postorder(tree->right);
        printf("%d\n", tree->val);
    }
}
void print_inorder(node * tree)
{
    if (tree) {
        print_inorder(tree->left);
        printf("%d\n", tree->val);
        print_inorder(tree->right);
    }
}

void main()
{
    node *tree;

    node *tmp;

    node *root = NULL;

    insert(&root, 10);
    insert(&root, 02);
    insert(&root, 15);
    insert(&root, 01);
    insert(&root, 19);
    insert(&root, 11);
    insert(&root, 17);
    insert(&root, 12);
    insert(&root, 3);
    insert(&root, 11);


    printf("Pre-order display\n");
    print_preorder(root);
    printf("in-order display\n");
    print_inorder(root);
    printf("post-order display\n");
    print_postorder(root);

    tmp = search(&root, 11);
    if(tmp)
        printf("Searched node=%d\n", tmp->val);
    else
        printf("data not found \n");

    delete(root);


}
