/*
 * Circular list
 */
#include<iostream>

struct node{
    int val;
    struct node *next;
};
class CircularList {
    public:
        void  clist_add_node(struct node **head, int val);
        void  clist_del_node(struct node **head, int val);
        void  clist_search_node(struct node *head, int val);
        void  clist_print(struct node *head);
};

void CircularList::clist_add_node(struct node **head, int val)
{
    struct node *tmp = *head;
    if(tmp == NULL) {
        tmp = (struct node *)malloc(sizeof(struct node));
        tmp->val = val;
        tmp->next = tmp;
    }
}
void CircularList::clist_print(struct node *head)
{
    struct node *tmp;
    return;
}

int main()
{
    struct node *head;
    class CircularList cl;
    cl.clist_add_node(&head,101);
}
