#include <iostream>
#include <stdlib.h>
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

int main(){
}
