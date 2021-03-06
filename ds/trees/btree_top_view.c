#include <iostream>
#include <stdlib.h>
using namespace std;
typedef struct node_s{
    struct node_s *left;
    struct node_s *right;
    int data;
}node;
void top_view(node *root, int level, int hlevel){
	if(root == NULL)
        return;
    top_view(root->left, level+1, hlevel-1);
    if(abs(level) == abs(hlevel)){
        cout << root->data << " ";
    }
    top_view(root->right, level+1, hlevel+1);
    return;
}

node *new_node(int data){
    node *node = new node;
    node->data = data;
    node->left = node->right = NULL;
    return node;
}
int main(){
    node *root = new_node(1);
    root->left = new_node(2);
    root->right = new_node(3);
    root->left->right = new_node(4);
    root->left->right->right = new_node(5);
    root->left->right->right->right = new_node(6);
    top_view(root,0,0);
    return 0;
}
