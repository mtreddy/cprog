
#ifndef GEN_LLIST_H__
#define GEN_LLIST_H__
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
void list_init(list *lst, void (*destroy)(void *data));
int list_rem_next(list *lst, elem *ele, void **data);
int list_ins_next(list *lst, elem *ele, void *data);
void list_destroy(list *lst);
void list_destroy(list *lst);
#endif
