#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <malloc.h>
#include "gen_llist.h"
void list_init(list *lst, void (*destroy)(void *data)){
    lst->head = NULL;
    lst->tail = NULL;
    lst->size = 0;
    lst->destroy = destroy;
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
int list_ins_next(list *lst, elem *ele, const  void *data)
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
void list_print_char(list *lst)
{
    elem *nxt = NULL;
    nxt = lst->head;
    while(nxt != NULL) {
        printf("%s\n", (char *)nxt->data);
        nxt = nxt->next;
    }
    return;
}

elem *list_reverse(list *lst){
    elem *prev=NULL;
    elem *curr=NULL;
    elem *next=NULL;
    curr=lst->head;
    while(curr != NULL){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
