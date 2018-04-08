#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <malloc.h>
#include "gen_llist.h"
/*
 * Expected to pass list struct pointer and destroy func pointer
 */
void ele_destroy(void *data) 
{
    return;
}
void list_string_test(list *lst)
{
    char data[5][5] = {"Hello", "how", "are", "You", "today"};
    list_ins_next(lst, NULL, (void *)data[0]);
    list_ins_next(lst, NULL, (void *)data[1]); 
    list_ins_next(lst, NULL, (void *)data[2]); 
    list_ins_next(lst, NULL, (void *)data[3]); 
    list_ins_next(lst, NULL, (void *)data[4]); 
    list_print_char(lst);
    //list_rem_next(&lst, NULL, (void *)&data); 
    
    lst->head = list_reverse(lst);
    list_print_char(lst);

}

void list_merge_test(list *lst) 
{
    return;
}
int rec_remove(elem *ele, int n){
    static int count = 0;
    
    if(ele == NULL)
        return  0;
    /*get len*/

    /* find pos*/
    count++;
}
int list_remove_nth_node_from_tail(list *lst, int n){
    printf("data=%d at pos=%d\n",rec_remove(lst->head, n), n);
}

int main(){

    list lst;
    list_init(&lst, &ele_destroy);
    if(0)
        list_string_test(&lst);
    if(0)
        list_merge_test(&lst);
    lst.head = (elem *)malloc(sizeof(elem));
    lst.head->data = (void *)1;
    lst.head->next = (elem *)malloc(sizeof(elem));
    lst.head->next->data = (void*)2;
    lst.head->next->next = (elem *)malloc(sizeof(elem));
    lst.head->next->next->data = (void*)3;
    lst.head->next->next->next = (elem *)malloc(sizeof(elem));
    lst.head->next->next->next->data = (void*)4;
    lst.head->next->next->next->next = (elem *)malloc(sizeof(elem));
    lst.head->next->next->next->next->data = (void*)5;
    lst.head->next->next->next->next->next = (elem *)malloc(sizeof(elem));
    lst.head->next->next->next->next->next->data = (void*)6;
    list_remove_nth_node_from_tail(&lst, 1);
}
