#include<stdlib.h>
#include<malloc.h>
#include "../lists/gen_llist.h"
#define PRIME_TBLSZ 351
typedef unsigned int  uint32;
typedef unsigned char uchar;
struct CHTbl{
    
    int buckets;
    int (*h)(void **data);
    int (*match)(void *key1, void *key2);
    void (*destroy)(void **data);
    list *table;
};
