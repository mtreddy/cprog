#include "btree.h"

int main(void)
{
    class btree btree;

    btree.root = NULL;

    btree.btree_insert_node(&btree.root, 10);
    btree.btree_insert_node(&btree.root, 02);
    btree.btree_insert_node(&btree.root, 15);
    btree.btree_insert_node(&btree.root, 1);
    btree.btree_insert_node(&btree.root, 12);
    btree.btree_insert_node(&btree.root, 3);
    btree.btree_insert_node(&btree.root, 19);
    btree.btree_insert_node(&btree.root, 5);
    btree.btree_insert_node(&btree.root, 25);

    printf("Pre-order display\n");
    btree.btree_print_preorder(btree.root);
}
