#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define CHUNK 0x100
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
    int free;
    struct alloc_t *next;
};

void *malloc_m(int len)
{
    struct alloc_t *node;
    if(membase == NULL) {
        membase = (uint32 *)malloc(MEMPOOL_SZ);
        memset((void*)membase,0,MEMPOOL_SZ);
        if(len >= MEMPOOL_SZ)
            return NULL;
        /*Initialize first node*/
        node = (struct alloc_t *)membase;
        node->free = 1;
        node->len = len;
        node->next = (struct alloc_t *)((uchar *)node+len);
        node->next->free = 0;
        /*We are representing next block len available*/
        node->next->len = MEMPOOL_SZ + (uint32)((uchar*)node->next) - ((uint32)((uchar *)membase) + sizeof(struct alloc_t));
        dbgpr("1 node 0x%llx node->len %d node->next 0x%llx node->next->len %d \n", node, node->len, node->next);
        return node;
    } else  {
        /*Get first available block with required size*/
        node = (struct alloc_t *)(membase);
        while((node->next != NULL) && (node->free == 1))
            node = node->next;
        if(node) {
            /* Find out the size */
            /* Node with free bit clear should hold the size available*/
            if(len > node->len)
                return NULL;
            node->len = len;
            node->free = 1;
            /*Initialize next node as well*/
            node->next = (struct alloc_t *)((uchar *)node + len);
            /*MEMPOOL_SZ - (node->next - membase)*/
            node->next->len = MEMPOOL_SZ + (uint32)((uchar*)node->next) 
                - ((uint32)((uchar *)membase) + sizeof(struct alloc_t));
            node->next->free = 0;
            node->next->next = NULL;

            dbgpr("2 node 0x%llx node->len %d node->next 0x%llx node->next->len %d \n", node, node->len, node->next, node->next->len);
            return((void *)(uchar*)node);
        }
    }
    return NULL;
}
void free_m(uint32 *mm)
{
    struct alloc_t *node, *tmp;
    node = (struct node *)membase;
    while((uint32*)node != mm){
        tmp = node;
        node = node->next;
    }
    if(node) {
        /*Combine this memory with adjacent free block*/
        /*See if parent is free memory*/
        if(tmp && tmp->free) {
            //tmp->len += node->len + (int)(sizeof(struct alloc_t));
            tmp->len += node->len;
            printf("Combining node 0x%x and node->next 0x%x into len  0x%x", (uint32 *)tmp, (uint32 *)tmp->next, tmp->len);
            tmp->next = node->next;
        } else if(node->next && node->next->free == 0) {
            tmp->next = node->next;
            //node->next->len += node->len + (int)(sizeof(struct alloc_t));
            node->next->len += node->len;
            printf("Combining node 0x%x and node->next 0x%x into len  0x%x", (uint32 *)node, (uint32 *)node->next, node->next->len);
        } else {
            node->free = 0;
            printf("freeing 0x%x\n", node);
        }

    } else {
        /*Failed to find the memory location to free*/
        return 1;
    }
}
int main(int argc, char** argv)
{
    uint32 *tt1, *tt2, *tt3, *tt4;

    tt1 = malloc_m(CHUNK);
    tt2 = malloc_m(CHUNK);
    tt3 = malloc_m(CHUNK);
    tt4 = malloc_m(CHUNK);

    free_m(tt1);
    free_m(tt2);
    free_m(tt3);
    free_m(tt4);

}

