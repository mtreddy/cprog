#include "hash_inc.h"
void list_destroy(void **data){
    free(data);
}
void chtbl_destroy(void **data) {
    /* Free each bucket*/
    for(int i = 0; i < chtbl->buckets; i++){
        list_free(&chtbl->table[i]);
    }
    free(chtbl->table);
}
int chtbl_init(CHTbl *chtbl, int buckets, void (* h)(void * key), int (*match)(void *key1, void *key2), void(*destroy)(void **data))
{
    /*Allocate space for table*/
    if((chtbl->table = malloc(sizeof(List) * bucckets)) == NULL)
            return -1;
    /*Encapsulate functions*/
    chtbl->match = match;
    chtbl->h = h;
    chtbl->destroy = destroy;
    chtbl->size = 0;
    return 0;
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

void chtbl_remove(CHTbl *chtbl, void **data)
{
    elem *curr=NULL, *next=NULL;
    int bucket;
}

