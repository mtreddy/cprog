#include <stdio.h>
#include <malloc.h>
/*
 * http://cslibrary.stanford.edu/110/BinaryTrees.html
 * Binary Search Tree Niche:
 * Basically, binary search trees are fast at insert and lookup. 
 * The next section presents the code for these two algorithms. 
 * On average, a binary search tree algorithm can locate a node 
 * in an N node tree in order lg(N) time (log base 2). Therefore,
 * binary search trees are good for "dictionary" problems where
 * the code inserts and looks up information indexed by some key.
 * The lg(N) behavior is the average case -- it's possible for a 
 * particular tree to be much slower depending on its shape.
 *
 */
#define FALSE 0
#define TRUE 1
struct node {
    int data;
    struct node *left;
    struct node *right;
};

int btree_lookup ( struct node *node, int data)
{
    if(node == NULL)
        return FALSE;
    else {
        if(node->data == data)
            return TRUE;
        else {
            if(node->data < data)
                   return btree_lookup(node->left, data); 
            else
                   return btree_lookup(node->left, data); 
        }
    }
}

void btree_print(struct node* node);
void btree_print_left(struct node* node)
{
    if(node == NULL) {
        return;
    } else {
        if(node->left)
           btree_print(node->left);
        else
            printf("left data=%d\n", node->data);
    }
}
void btree_print_right(struct node* node)
{
    if(node == NULL) {
        return;
    } else {
        if(node->right)
           btree_print(node->right);
        else
            printf("right data=%d\n", node->data);
    }
}
void btree_print(struct node* node)
{
    if(node == NULL) {
        return;
    } else {
        btree_print(node->left);
        if(node) 
            printf("data=%d\n", node->data);
        btree_print(node->right);
    }
}
void btree_print_pre_order(struct node* node)
{
    if(node == NULL) {
        return;
    } else {
        if(node) 
            printf("data=%d\n", node->data);
        btree_print(node->left);
        btree_print(node->right);
    }
}
void btree_print_post_order(struct node* node)
{
    if(node == NULL) {
        return;
    } else {
        btree_print(node->left);
        btree_print(node->right);
        if(node) 
            printf("data=%d\n", node->data);
    }
}
int btree_len(struct node* node)
{
    if(node == NULL)
        return 0;
    } else {
        return(btree_len(node->left) + 1 + btree_len(node->right));
    }
}
struct node* btree_new_node(int data) {
    struct node* node = (struct node *)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return(node);
}

int btree_max_depth(struct node* node) 
{
    if(node == NULL) {
        return 0;
    } else {
        /*compute the depth of each subtree*/
        int l_depth = btree_max_depth(node->left);
        int r_depth = btree_max_depth(node->right);
        /*Use the larger one*/
        if(l_depth > r_depth)
            return(l_depth + 1);
        else
            return(r_depth + 1);
    }
}
int btree_min_value(struct node* node)
{
    struct node* current = node;

    while(current->left != NULL) {
        current = current->left;
    }
    return current->data;
}
/* 
 *  Given a tree and a sum, return true if there is a path from the root 
 *  down to a leaf, such that adding up all the values along the path 
 *  equals the given sum.
 *  Strategy: subtract the node value from the sum when recurring down, 
 *  and check to see if the sum is 0 when you run out of tree. 
 */ 
int btree_has_path_sum(struct node* node, int sum)
{
    /* Return true if we run out of tree and sum==0*/
    if(node == NULL) {
        return (sum == 0);
    } else {
        /*Otherwise check both subtrees*/
        int sub_sum = sum - node->data;
        return(btree_has_path_sum(node->left, sub_sum) || 
              btree_has_path_sum(node->right, sub_sum))
    }
}
/* 
 Change a tree so that the roles of the 
 left and right pointers are swapped at every node.
 So the tree... 
       4 
      / \ 
     2   5 
    / \ 
   1   3

 is changed to... 
       4 
      / \ 
     5   2 
        / \ 
       3   1 
*/ 
void btree_mirror(struct node* node) { 
  if (node==NULL) { 
    return; 
  } 
  else { 
    struct node* temp;

    // do the subtrees 
    btree_mirror(node->left); 
    btree_mirror(node->right);

    // swap the pointers in this node 
    temp = node->left; 
    node->left = node->right; 
    node->right = temp; 
  } 
} 

/* 
 For each node in a binary search tree, 
 create a new duplicate node, and insert 
 the duplicate as the left child of the original node. 
 The resulting tree should still be a binary search tree.
 So the tree... 
    2 
   / \ 
  1   3

 Is changed to... 
       2 
      / \ 
     2   3 
    /   / 
   1   3 
  / 
 1

*/ 
void doubleTree(struct node* node) { 
  struct node* oldLeft;

  if (node==NULL) return;

  // do the subtrees 
  doubleTree(node->left); 
  doubleTree(node->right);

  // duplicate this node to its left 
  oldLeft = node->left; 
  node->left = newNode(node->data); 
  node->left->left = oldLeft; 
} 
/* 
 Given two trees, return true if they are 
 structurally identical. 
*/ 
int sameTree(struct node* a, struct node* b) { 
  // 1. both empty -> true 
  if (a==NULL && b==NULL) return(true);
  // 2. both non-empty -> compare them 
  else if (a!=NULL && b!=NULL) { 
    return( 
      a->data == b->data && 
      sameTree(a->left, b->left) && 
      sameTree(a->right, b->right) 
    ); 
  } 
  // 3. one empty, one not -> false 
  else return(false); 
} 
/* 
 For the key values 1...numKeys, how many structurally unique 
 binary search trees are possible that store those keys.
 Strategy: consider that each value could be the root. 
 Recursively find the size of the left and right subtrees. 
*/ 
int countTrees(int numKeys) {

  if (numKeys <=1) { 
    return(1); 
  } 
  else { 
    // there will be one value at the root, with whatever remains 
    // on the left and right each forming their own subtrees. 
    // Iterate through all the values that could be the root... 
    int sum = 0; 
    int left, right, root;

    for (root=1; root<=numKeys; root++) { 
      left = countTrees(root - 1); 
      right = countTrees(numKeys - root);

      // number of possible trees with this root == left*right 
      sum += left*right; 
    }

    return(sum); 
  } 
} 
/* 
 Returns true if a binary tree is a binary search tree. 
*/ 
int isBST(struct node* node) { 
  if (node==NULL) return(true);
  // false if the max of the left is > than us

  // (bug -- an earlier version had min/max backwards here) 
  if (node->left!=NULL && btree_max_value(node->left) > node->data) 
    return(false);

  // false if the min of the right is <= than us 
  if (node->right!=NULL && btree_min_value(node->right) <= node->data) 
    return(false);

  // false if, recursively, the left or right is not a BST 
  if (!isBST(node->left) || !isBST(node->right)) 
    return(false);

  // passing all that, it's a BST 
  return(true); 
} 
/* 
 Returns true if the given tree is a binary search tree 
 (efficient version). 
*/ 
int isBST2(struct node* node) { 
  return(isBSTUtil(node, INT_MIN, INT_MAX)); 
}
/* 
 Returns true if the given tree is a BST and its 
 values are >= min and <= max. 
*/ 
int isBSTUtil(struct node* node, int min, int max) { 
  if (node==NULL) return(true);

  // false if this node violates the min/max constraint 
  if (node->data<min || node->data>max) return(false);

  // otherwise check the subtrees recursively, 
  // tightening the min or max constraint 
  return 
    (isBSTUtil(node->left, min, node->data) && 
    isBSTUtil(node->right, node->data+1, max) 
  ); 
}     
 
int btree_change_root()
{

}

struct node* btree_insert(struct node* node, int data){
    if(node == NULL) {
        return(btree_new_node(data));
    } else {
        if(data < node->data) node->left = btree_insert(node->left, data);
        else node->right = btree_insert(node->right, data);
        return(node);
    }
}

struct node* btree_build123() {
    struct node* root, node1, node2;

    root = btree_new_node(2);
    root->left =  btree_new_node(1);
    root->right = btree_new_node(3);
    return(root);
}
struct node * btree_build123_1(struct node* node) {
    struct node* tmp;
    tmp = btree_insert(node, 1);
    tmp = btree_insert(tmp, 2);
    tmp = btree_insert(tmp, 4);
    tmp = btree_insert(tmp, 3);
    return tmp;
}

int main()
{
    struct node* root=NULL;
    //root = btree_build123();
    root = btree_build123_1(root);
    btree_print(root);
    return 0;
}
