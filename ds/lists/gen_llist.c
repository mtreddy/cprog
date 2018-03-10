#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <malloc.h>
/*
 * List element struct
 */
typedef struct elem_s{
    void *data;
    struct elem_s *next;
    struct elem_s *prev;
}elem;

typedef struct list_s{
    elem *head;
    elem *tail;
    int size;
    void (*destroy)(void *data);
    int (*match)(const elem *key1, const elem *key2);
}list;
#define list_head(list) list->head
#define list_tail(list) list->tail
#define list_size(list) list->size
#define list_next(ele) ele->next
#define list_data(ele) ele->data
#define list_is_head(list, ele) ((list)->head == (ele) ? 1 : 0)
#define list_is_tail(list, ele) ((list)->tail == (ele) ? 1 : 0)
/*
 * Expected to pass list struct pointer and destroy func pointer
 */
void list_init(list *lst, void (*destroy)(void *data)){
    lst->head = NULL;
    lst->tail = NULL;
    lst->size = 0;
    lst->destroy = destroy;
    return;
}
void ele_destroy(void *data) 
{
    return;
}
int list_rem_next(list *lst, elem *ele, void **data) {
    elem *old_ele;
    /*If ele is NULL remove the first element*/
    if(ele == NULL) {
        if(list_size(lst) == 0)
            return -1;
        old_ele = lst->head;
        *data = old_ele->data;
        lst->head = ele->next->next;
        old_ele->next = NULL;
        if(list_size(lst) == 1)
            lst->tail = NULL;
    } else {
        /*If this is tail*/
        if(ele->next == NULL)
            return -1;
        /* ele is int he middle of lst*/
        *data = ele->next->data;
        old_ele = ele->next;
        ele->next = ele->next->next;
        old_ele->next = NULL;
        /* if ele->next is tail */
        if(ele->next == NULL)
            lst->tail = ele;
    }
    lst->size--;
    free(old_ele);
    /* If ele is not NULL then find next ele which is not NULL to delete*/
}
/*
 * List struct pointer
 * ele which need to be removed.
 * if ele is NULL then we remove first element in the list.
 * if not NULL then we search for the match element and delete it.
 */
int list_ins_next(list *lst, elem *ele, void *data)
{
    elem *newele = NULL;
    if((newele = (elem *) malloc(sizeof(ele))) == NULL)
        return -1;
    /*iF element is NULL then just added at the head*/
   if(ele == NULL) {
       if(list_size(lst) == 0)
           lst->tail = newele;
       newele->next = lst->head;
       newele->data = (void *)data;
      lst->head =  newele;
   } else {
       /*Otherwise add to element->next*/
       /*Element is tail*/
       if(ele->next == NULL) {
           lst->tail = newele;
       }
       newele = (void *)data;
       newele->next = ele->next;
       ele->next = newele;
   }
   lst->size++;
   return 0;

}
void list_destroy(list *lst)
{
    void *data;
    while(list_size(lst) > 0) {
        if(list_rem_next(lst, NULL, (void **)&data) && lst->destroy != NULL)
            lst->destroy(data);
    }
    memset(lst, 0, sizeof(list));
    return;
}
int main(){

    list lst;
    int data;
    list_init(&lst, &ele_destroy);
    list_rem_next(&lst, NULL, (void *)&data); 
    
}
