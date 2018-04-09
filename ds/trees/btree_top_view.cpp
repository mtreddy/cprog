#include <iostream>
#include <stdlib.h>
using namespace std;
struct node{
    struct node *left;
    struct node *right;
    int data;
};
void top_view(node *root, int level, int hlevel){
	if(root == NULL)
        return;
    top_view(root->left, level+1, hlevel-1);
    if(abs(level) == abs(hlevel)){
        cout << root->data << " " << level << " " << hlevel << endl;
        if(hlevel == 0) {
            level = 0;
        }
    }
    top_view(root->right, level+1, hlevel+1);
    return;
}

node *new_node(int data){
    struct node* nd = new node;
    nd->data = data;
    nd->left = nd->right = NULL;
    return nd;
}
int main(){
    node *root = new_node(1);
    root->left = new_node(2);
    root->right = new_node(3);
    root->left->right = new_node(4);
    root->left->right->right = new_node(5);
    root->left->right->right->right = new_node(6);
    cout << endl;
    top_view(root,0,0);
    cout << endl;
    return 0;
}
