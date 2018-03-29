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
    void (*destroy)(void **data);
    int size;
    list *table;
}CHTbl;
