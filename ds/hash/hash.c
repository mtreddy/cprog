#include "hash_inc.h"
//void list_destroy(list *lst){
//    return;
//}
void chtbl_destroy(CHTbl *chtbl, void **data) {
    /* Free each bucket*/
    for(int i = 0; i < chtbl->buckets; i++){
        list_destroy(&chtbl->table[i]);
    }
    free(chtbl->table);
}
int chtbl_init(CHTbl *chtbl, int buckets, int (* h)(void * key), int (*match)(void *key1, void *key2), void(*destroy)(void **data))
{
    /*Allocate space for table*/
    if((chtbl->table = malloc(sizeof(list) * buckets)) == NULL)
            return -1;
    /*Encapsulate functions*/
    chtbl->match = match;
    chtbl->h = h;
    chtbl->destroy = destroy;
    chtbl->size = 0;
    return 0;
}
int chtbl_lookup(CHTbl *chtbl, void **data)
{
    int bucket;
    elem *ele;
    /* Hash the key*/
    bucket = (chtbl->h(*data)) % chtbl->buckets;
    /*Search for the data in bucket*/
    for(ele=list_head(&chtbl->table[bucket]); ele != NULL; ele=list_next(ele)){
        if(chtbl->match(data, list_data(ele))) {
            *data = list_data(ele);
            return 0;
        }
    }

    return -1;
}
int chtbl_insert(CHTbl *chtbl, void **data)
{
    int bucket, retval;
    void *temp;
    temp = (void *)data;
    /*Check if element already in table*/
    if(chtbl_lookup(chtbl, &temp) == 0)
        return 1;
    /* Hash the key*/
    bucket = chtbl->h(data) % chtbl->buckets;
    /*Insert the data into the bucket*/
    if((retval = list_ins_next(&chtbl->table[bucket], NULL, data)) == 0){
        chtbl->size++;
    }

}
int chtbl_remove(CHTbl *chtbl, void **data)
{
    elem *curr=NULL, *prev=NULL;
    int bucket;
    void *temp;
    temp = (void *)data;
    /* has the key*/
    bucket = chtbl->h(*data) % chtbl->buckets;
    /*search for the element*/
    for(curr=list_head(&(chtbl->table[bucket])); curr != NULL; curr=list_next(curr)){
        if(chtbl->match(data, list_data(curr))) {
            if(list_rem_next(&chtbl->table[bucket], prev, data)){
                chtbl->size--;
                return 0;
            } else {
                return -1;
            }
        }
       prev = curr; 
    }
}

