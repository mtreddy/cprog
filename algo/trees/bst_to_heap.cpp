/*
 *  In-place Convert BST into a Min-Heap
 *  Given a Binary Search Tree, convert it into a Min-Heap containing the same elements in O(n) time. Do this in-place.

 *  Input: Binary Search Tree
 *          8
 *       /    \
 *      4      12
 *    /  \     /  \
 *   2    6   10  14


 *  Output - Min Heap
 *         2
 *       /    \
 *     4        6
 *   /  \     /   \
 *  8    10  12   14
 *  [Or any other tree that follows Min Heap
 *   properties and has same keys]
 *  We strongly recommend you to minimize your browser and try this yourself first.

 *  If we are allowed to use extra space, we can perform inorder traversal of the tree and store the keys in an auxiliary 
 *  array. As we’re doing inorder traversal on a BST, array will be sorted. Finally, we construct a complete binary tree 
 *  from the sorted array. We construct the binary tree level by level and from left to right by taking next minimum element 
 *  from sorted array. The constructed binary tree will be a min-Heap. This solution works in O(n) time, but is not in-place.

 *  How to do it in-place?
 *  The idea is to convert the binary search tree into a sorted linked list first. We can do this by traversing the BST in 
 *  inorder fashion. We add nodes at the beginning of current linked list and update head of the list using pointer to head pointer. 
 *  Since we insert at the beginning, to maintain sorted order, we first traverse the right subtree before the left subtree. i.e. do a reverse inorder traversal.

 *  Finally we convert the sorted linked list into a min-Heap by setting the left and right pointers appropriately. 
 *  We can do this by doing a Level order traversal of the partially built Min-Heap Tree using queue and traversing the 
 *  linked list at the same time. At every step, we take the parent node from queue, make next two nodes of linked list as 
 *  children of the parent node, and enqueue the next two nodes to queue. As the linked list is sorted, the min-heap property is maintained.

 *  Below is C++ implementation of above idea –
 */

// Program to convert a BST into a Min-Heap
// in O(n) time and in-place
#include <iostream>
#include <queue>
using namespace std;

// Node for BST/Min-Heap
struct Node
{
    int data;
    Node *left, *right;
};

// Utility function for allocating node for BST
Node* newNode(int data)
{
    Node* node = new Node;
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Utility function to print Min-heap level by level
void printLevelOrder(Node *root)
{
    // Base Case
    if (root == NULL) return;

    // Create an empty queue for level order traversal
    queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        int nodeCount = q.size();
        while (nodeCount > 0)
        {
            Node *node = q.front();
            cout << node->data << " ";
            q.pop();
            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);
            nodeCount--;
        }
        cout << endl;
    }
}

// A simple recursive function to convert a given
// Binary Search tree to Sorted Linked List
// root  --> Root of Binary Search Tree
// head_ref --> Pointer to head node of created
//           linked list
void BSTToSortedLL(Node* root, Node** head_ref)
{
    // Base cases
    if(root == NULL)
        return;

    // Recursively convert right subtree
    BSTToSortedLL(root->right, head_ref);

    // insert root into linked list
    root->right = *head_ref;

    // Change left pointer of previous head
    // to point to NULL
    if (*head_ref != NULL)
        (*head_ref)->left = NULL;

    // Change head of linked list
    *head_ref = root;

    // Recursively convert left subtree
    BSTToSortedLL(root->left, head_ref);
}

// Function to convert a sorted Linked
// List to Min-Heap.
// root --> Root of Min-Heap
// head --> Pointer to head node of sorted
//           linked list
void SortedLLToMinHeap(Node* &root, Node* head)
{
    // Base Case
    if (head == NULL)
        return;

    // queue to store the parent nodes
    queue<Node *> q;

    // The first node is always the root node
    root = head;

    // advance the pointer to the next node
    head = head->right;

    // set right child to NULL
    root->right = NULL;

    // add first node to the queue
    q.push(root);

    // run until the end of linked list is reached
    while (head)
    {
        // Take the parent node from the q and remove it from q
        Node* parent = q.front();
        q.pop();

        // Take next two nodes from the linked list and
        // Add them as children of the current parent node
        // Also in push them into the queue so that
        // they will be parents to the future nodes
        Node *leftChild = head;
        head = head->right;  // advance linked list to next node
        leftChild->right = NULL; // set its right child to NULL
        q.push(leftChild);

        // Assign the left child of parent
        parent->left = leftChild;

        if (head)
        {
            Node *rightChild = head;
            head = head->right; // advance linked list to next node
            rightChild->right = NULL; // set its right child to NULL
            q.push(rightChild);

            // Assign the right child of parent
            parent->right = rightChild;
        }
    }
}

// Function to convert BST into a Min-Heap
// without using any extra space
Node* BSTToMinHeap(Node* &root)
{
    // head of Linked List
    Node *head = NULL;

    // Convert a given BST to Sorted Linked List
    BSTToSortedLL(root, &head);

    // set root as NULL
    root = NULL;

    // Convert Sorted Linked List to Min-Heap
    SortedLLToMinHeap(root, head);
}

// Driver code
int main()
{
    /* Constructing below tree
                8
            / \
            4    12
        / \ / \
        2 6 10 14
    */

    Node* root = newNode(8);
    root->left = newNode(4);
    root->right = newNode(12);
    root->right->left = newNode(10);
    root->right->right = newNode(14);
    root->left->left = newNode(2);
    root->left->right = newNode(6);

    BSTToMinHeap(root);

    /* Output - Min Heap
                2
            / \
            4    6
        / \ / \
        8 10 12 14
    */

    printLevelOrder(root);

    return 0;
}

