#include<stdio.h>
#include<malloc.h>

typedef struct lele_s{
    struct lele_s *next;
    struct lele_s *prev;
    void * data;
}elem;

typedef struct list_s {
    elem *head;
    elem *tail;
    int (* destroy) (void *data);
    int (* match) (void *key1, void *key2);
}list;
elem * list_find_ele(elem *ele, list *list)
{
    elem *tmp;
    /*Check if ele is not NULL*/
    tmp = list->head;

    if(ele == NULL)
        return NULL;
    /*Check if head is not NULL*/
    if(tmp == NULL)
        return NULL;
    /*Find the element*/
    while(tmp->next) {
        /*Found it*/
        if(ele == tmp)
            return tmp;
    }
    /*Element is not in the list*/
    return NULL;

}
/*
 * Possible cases
 * 1. list is empty
 * 2. ele passed is empty
 * 3. ele is first one
 * 4. ele is in the middile of list
 * 5. ele is at the end
 *
 */
void remove_ele(elem *ele, list *list)
{
    elem *tmp=NULL, *prev=NULL;
    /*1 */
    if(list->head == NULL)
        return ;
    /*2 */
    if(ele == NULL)
        return ;
    /*3*/
    tmp = list->head;
    if(tmp == ele) {
        free(tmp);
        list->head = NULL;
        return;
    }
    /*4 & 5*/ 
    while(tmp) {
        if(tmp == ele) {
            prev->next = tmp->next;
            prev->next->prev = prev;
            tmp->next = NULL;
            tmp->prev = NULL;
            free(tmp);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }

}
/*
 * Add element given data
 * 1. list empty
 * 2. middle ele need to be added
 * 3. last to be added
 */
void add_ele(void* data, list *list)
{
    elem *tmp = NULL, *prev = NULL;
    /* 1 */
    if(list->head == NULL) {
        tmp = (elem*)malloc(sizeof(elem));
        tmp->next = NULL;
        tmp->prev = NULL;
        tmp->data = (int *)data;
    }

    /* 2 */
    /* 3 */
    tmp = list->head;

    while(tmp) {
        prev = tmp;
        tmp = tmp->next;

    }

    tmp->next = (elem *)malloc(sizeof(elem));
    tmp->next->next = NULL;
    tmp->prev = prev;
    return;
}
void list_init(list *lst, int (*destroy)(void *data))
{
    lst->head = NULL;
    lst->tail = NULL;
    lst->destroy = destroy;
}
elem* dlist_SortedInsert(elem *head,int data)
{
    // Complete this function
   // Do not write the main method. 
    // cout << "data= " << data << endl;
    elem *tmp=NULL, *curr=NULL, *prev=NULL, *next=NULL;
    tmp = (elem *)malloc(sizeof(elem));
    tmp->next = NULL;
    tmp->prev = NULL;
    tmp->data = (void *)data;
    if(head == NULL){
        head = tmp;
        //cout << "data= " << data << endl;
        return head;
    }
    curr = head;
    while(curr){
        //cout << "data= " << data << endl;
        next = curr->next;
        if(curr->data >= (void *)data){
             if(prev == NULL){/*Inserting at head*/
                tmp->next = curr;
                curr->prev = tmp;
                head = tmp;
                return head;
            } else{
                prev->next = tmp;
                tmp->next = curr;
                tmp->prev = prev;
                curr->prev = tmp;
                return head;
            }
        }        
        prev = curr;
        curr = next;
    }
    prev->next = tmp;
    tmp->prev = prev;
 //   tmp=head;
 //   while(tmp){
 //       cout << tmp->data << " " ;
 //       tmp=tmp->next;
 //   }
    return head;
}   
elem * dliest_reverse(elem *head)
{
    elem *prev=NULL, *curr=NULL, *next=NULL;
    if(head == NULL)
        return NULL;
    curr = head;
    while(curr){
        prev = curr->prev;
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        if(curr == NULL)
            break;
    }
    head = prev;
    return head;
}
int destroy(void *data)
{
    /*need to implement*/
    return 0;
}
int main()
{
    /*
     *  Root
     */
    list lst;
    list_init(&lst, destroy);
    /*
     * Add a member
     */

    /*
     * Traverse
     */

    /*
     * Print
     */

    /*
     * Delete
     */
    return 0;
}
