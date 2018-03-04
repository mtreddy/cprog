#include <iostream>
#include <malloc.h>

struct node{
    struct node *left;
    struct node *right;
    int val;
};
typedef struct node bnode;

class btree {
    public:
        node *root;    
        int btree_insert_node(node **tree, int val);
        node* btree_search_node(node **btree, int val);
        void btree_delete_node(node *tree);
        void btree_print_preorder(node *tree);
        void btree_print_postorder(node *tree);
        void btree_print_inorder(node *tree);
};

int btree::btree_insert_node(node **tree, int val) {
    node *temp = NULL;

    if(*tree == NULL) {
        temp=(node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->val = val;
        *tree = temp;
        return 0;
    }

    if((*tree)->val > val) {
        btree_insert_node(&(*tree)->right, val);
    } else {
        btree_insert_node(&(*tree)->left, val);
    }
    return 0;
}
node* btree::btree_search_node(node **btree, int val){

    if(*btree == NULL) 
        return NULL;

    if((*btree)->val == val)
        return *btree;
    else if((*btree)->val < val)
        btree_search_node(&((*btree)->left), val);
    else
        btree_search_node(&((*btree)->right), val);
}
void btree::btree_delete_node(node *tree) {
    if(tree) {
        btree_delete_node(tree->left);
        btree_delete_node(tree->right);
        free(tree);
    }
}
void btree::btree_print_preorder(node *tree) {
    if (tree) {
        printf("%d\n", tree->val);
        btree_print_preorder(tree->left);
        btree_print_preorder(tree->right);
    }
}
void btree::btree_print_postorder(node *tree) {
    if (tree) {
        btree_print_postorder(tree->left);
        btree_print_postorder(tree->right);
        printf("%d\n", tree->val);
    }
}
void btree::btree_print_inorder(node *tree) {
    if (tree) {
        btree_print_inorder(tree->left);
        printf("%d\n", tree->val);
        btree_print_inorder(tree->right);
    }
}


