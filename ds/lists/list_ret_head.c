#include<stdio.h>
#include<malloc.h>


struct Node{
    int data;
    struct Node *next;
};
typedef struct Node  Node;

Node* Insert(Node *head,int data)
{
  // Complete this method
    Node *tmp;
    tmp = head;
    if(head == NULL){
        tmp = (struct Node *)malloc(sizeof(struct Node));
        tmp->data = data;
        tmp->next = NULL;
        return tmp;
    }
    tmp = head;
    while(tmp->next) {
        tmp = tmp->next;
    }

    tmp->next = (struct Node *)malloc(sizeof(struct Node));
    tmp->next->data = data;
    tmp->next->next = NULL;
    return head;

}
void print_list(Node *head)
{
    Node *tmp;
    tmp = head;


    while(tmp) {
        printf("data=%d\n", tmp->data);
        tmp = tmp->next;
    }
}

int main()
{
    int val = 0;	
    Node *head = NULL;

    head = Insert(head, 10);
    print_list(head);
    head = Insert(head, 100);
    print_list(head);
}

