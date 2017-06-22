#include "list.h"

int main(void)
{
    class llist nlist;
    struct node *temp;
    int val;
    nlist.list_init();
    nlist.list_add_node(&nlist.root);
    nlist.list_del_node(val);
    nlist.list_print();
    return 0;
}
