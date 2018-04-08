#include<stdlib.h>
#include<malloc.h>
#include "../lists/gen_llist.h"
#define PRIME_TBLSZ 351
typedef unsigned int  uint32;
typedef unsigned char uchar;
typedef struct CHTbl_{
    int buckets;
    int (*h)(void *data);
    int (*match)(void *key1, void *key2);
    void (*destroy)(struct CHTbl_ *chtbl, void **data);
    int size;
    list *table;
}CHTbl;
void chtbl_destroy(CHTbl *chtbl, void **data);
int chtbl_init(CHTbl *chtbl, int buckets, int (* h)(void * key), int (*match)(void *key1, void *key2), void(*destroy)(CHTbl *chtbl, void **data));
int chtbl_lookup(CHTbl *chtbl, void **data);
int chtbl_insert(CHTbl *chtbl, void **data);
int chtbl_remove(CHTbl *chtbl, void **data);
