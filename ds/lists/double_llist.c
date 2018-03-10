#include<stdio.h>

typedf struct lele_s{
    struct lele_t *next;
    (void *) data;
}lele_t

typdef struct list_s {
    lele_t *head;
    lele_t *tail;
    int (* destroy) (voit *data);
    int (* match) (void *key1, void *key2);
}list_t;
i
list_t list;

lele_t * list_find_ele(lele_t *ele, list_t *list)
{
    lele_t *tmp;
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
int remove_ele(lele_t *ele, list_t *list)
{
    lele_t *tmp=NULL, *prev=NULL;
    /*1 */
    if(list->head == NULL)
        return -1;
    /*2 */
    if(ele == NULL)
        return -1;
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
void add_ele(void* data, list_t *list)
{
    lele_t *tmp = NULL, *prev = NULL;
    /* 1 */
    if(list->head == NULL) {
        ele = (lele_t *) mallco(sizeof(lele_t));
        ele->next = NULL;
        ele->prev = NULL;
        else->data = (int *)data;
    }

    /* 2 */
    /* 3 */
    tmp = list->head;

    while(tmp) {
        prev = tmp;
        tmp = tmp->next;

    }

    tmp->next = (lele_t *)malloc(sizeof(lele_t));
    tmp->next->next = NULL;
    tmp->prev = prev;
    return;
}
int list_init(int (* fn)(lele_t *ele, list_t *list))
{
    list->head = NULL;
    list->tail = NULL;
}
int main()
{
    /*
     *  Root
     */

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
}
