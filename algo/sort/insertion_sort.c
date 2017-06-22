#include<stdio.h>
#include<malloc.h>
#include "sort_common.h"
/*
 * gcc.c4.2.1-p4a.x86_64 -g3 insertion_sort.c  -o insertion_sort
 */
#define DATASIZE 25
int data1[25] = {25,22,23,21,19,24,18,20,17,14,16,13,15,12,10,11,9,7,8,6,4,5,3,1,2};

struct dlist *root;

int list_add_data(int data, struct dlist *head)
{
     struct dlist *tmp = NULL;

     if(head == NULL) {
        head = (struct dlist *)malloc(sizeof(struct dlist));
        head->data = data;
        head->next = NULL;
        head->prev = NULL;
        root = head; // <<--- this is where external variable root is set hear.
        return 0;
     }
    
     tmp = head;
     while(tmp) {
         if(tmp->next == NULL) {
            tmp->next = (struct dlist *)malloc(sizeof(struct dlist));
            tmp->next->data = data;
            tmp->next->next = NULL;
            tmp->next->prev = tmp;
            return 0;
        }
         tmp = tmp->next;
     }
}
int swap_nodes(struct dlist **node1, struct dlist **node2) {
    struct dlist *tmp;
    if(((*node1) == NULL) || ((*node2) == NULL))
        return -1;
    tmp = (*node1)->next;
    (*node1)->next = (*node2)->next;
    (*node2)->next = tmp;
    tmp = (*node1)->prev;
    (*node1)->prev = (*node2)->prev;
    (*node2)->prev = tmp;
}
int list_print_data(struct dlist *head)
{
    struct dlist *tmp = NULL;

    tmp = head;

    while(tmp) {
        printf(" %3d ", tmp->data);
        tmp = tmp->next;
    }
    printf("\n");
    return 0;
}
int insertion_sort_using_list()
{
    int i = 0, j=0;
    int *data;
    int *ddata;
    struct dlist *head = NULL;
    int len = DATASIZE;
    //data = (int *)malloc(sizeof(int)*DATASIZE);
    //ddata = (int *)malloc(sizeof(int)*DATASIZE);
    data = &data1[0]; 
    //fill_data(DATASIZE, data);
    /*print input list*/
    for(i=0;i<DATASIZE; i++)
        list_add_data(data1[i], root);
    /* print intermidiate list*/
    struct dlist   *tmp = NULL;
    struct dlist   *tmp1 = NULL;
    tmp1 = root;
    tmp = tmp1->next;
    list_print_data(root);
    while(tmp) {
        if(tmp1->data > tmp->data)
            swap_nodes(&tmp1, &tmp);
        tmp = tmp->next;
        list_print_data(root);
    }
    /* print final list*/
    list_print_data(root);
}
/*
 *
 INSERTION-SORT.A/
    1 for j = 1 to A.length
    2 key = A[j]
    3 // Insert A[j]  into the sorted sequence A[1 ... j- 1].
    4 i = j - 1
    5   while i >= 0 and A[i] > key
    6       A[i + 1]  = A[i]
    7       i = i - 1
    8   A[i+1] = key
 */
int insertion_sort_array()
{
    int i, j;
    int key = 0;
    for(j = 1; j < sizeof(data1)/sizeof(int);  j++) {
        key= data1[j];
        i = j - 1;
        while((i >= 0) && (data1[i] >  key)){
            data1[i + 1] = data1[i];
            i = i - 1;
        }
        data1[i+1] = key;
        PRINT_ARRAY(25, data1);
    }
    PRINT_ARRAY(25, data1);

}
int main()
{
    insertion_sort_array();
}
