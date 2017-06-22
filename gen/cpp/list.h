#include<malloc.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
struct node{
    struct node *next;
    struct node *prev;
    int val;
};

class llist{
    public:
    struct node *root; 
    void list_init(void);
    int list_add_node(struct node **ele);
    int list_del_node(int val);
    int list_search_node(struct node *ele);
    int list_print(void);
};

void llist::list_init(void)
{
    cout << "Initialized\n";
}

int llist::list_add_node(struct node **ele) {
    cout<<  "Added node\n";
}
int llist::list_del_node(int val) {
    cout<<  "Deleted node\n";
}
int llist::list_print(void) {
    cout<<  "Printing list\n";
}
