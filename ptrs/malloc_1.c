#include <stdio.h>
#include <malloc.h>

#define CHUNK 1024
#define MEMPOOL_SZ  1024*1024*2
#define DEBUG_MALLOC 1
#ifdef DEBUG_MALLOC
#define dbgpr printf
#else
#define dbgerr printf
#define dbgpr
#endif
typedef unsigned int uint32;
typedef unsigned char uchar;

static uint32 * membase;
static int avlbl_mem = MEMPOOL_SZ;
struct alloc_t{
    int len;
    struct alloc_t *next;
};

void *malloc_m(int len)
{
    struct alloc_t *tt;
  
    if(avlbl_mem < len) {
        printf("Not enough memory available\n");
        return NULL;
    }
    tt = (struct alloc_t *)(membase);
    while(tt->len != 0)
        tt = tt->next;

    tt->len = len;
    tt->next = (struct alloc_t *)(((uchar *)tt + len) + sizeof(struct alloc_t));
    avlbl_mem -= len;
    tt->next->len = 0;
    tt->next->next = NULL;
    dbgpr("tt 0x%llx tt->len %d tt->next 0x%llx tt->next->len %d \n", tt, tt->len, tt->next, tt->next->len);
    return((void *)((uchar*)tt + sizeof(struct alloc_t)));
}
void free_m(uint32 *mm)
{
    struct alloc_t *tt, *ttt;
    tt = membase;

    while(tt){
        if(tt == (struct alloc_t *)((uchar*)mm - (sizeof(struct alloc_t)))){
            ttt = tt;
            tt = tt->next;
            avlbl_mem += ttt->len;
            dbgpr("Freed memory at tt->next 0x%x len %d\n", ttt, ttt->len);
            ttt->len = 0;
            return;
        }
        tt = tt->next;
    }
}
int main(int argc, char** argv)
{
    uint32 *tt1, *tt2, *tt3;
    membase = (uint32 *)malloc(MEMPOOL_SZ);
    bzero((void*)membase,MEMPOOL_SZ);


    tt1 = malloc_m(CHUNK);
    tt2 = malloc_m(CHUNK);
    tt3 = malloc_m(CHUNK);

    free_m(tt1);
    free_m(tt2);
    free_m(tt3);
    
}


