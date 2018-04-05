#include <stdio.h>
#include <stdlib.h>

#if defined(DATASIZE_10)
int data[10];
#endif
#if defined(DATASIZE_25)
int data[25];
#endif
#if defined(DATASIZE_50)
int data[50];
#endif
#if defined(DATASIZE_100)
int data[100];
#endif
#if defined(DATASIZE_1000)
int data[1000];
#endif

struct slist{
    int data;
    struct slist *next;
}slist_t;

struct dlist{
    int data;
    struct dlist *next;
    struct dlist *prev;
}dlist_t;


static void fill_data(int len, int *buf) {  
    int i; for(i=0; i < len; i++) { *(buf + i) = rand();}
}

static void show_data(int len, int *buf) {  
    int i; for(i=0; i < len; i++) 
        printf(" ele %d data %d\n", i,  *(unsigned int *)(buf + i)); 
}
#define PRINT_ARRAY( len, data) ({ \
    int i = 0; \
    for(i = 0; i < len; i++) \
        printf(" %3d ", data[i]); \
    printf("\n"); \
} ) 
static void show_data_flat(int len, int *buf) {  
    int i; for(i=0; i < len; i++) 
        printf(" %d ", *(unsigned int *)(buf + i)); 
    if(i%15 == 0)
        printf("\n");
        
    printf("\n");
}

void swap(int *a, int *b)
{
    int tmp = 0;
    tmp = *a;
    *a = *b;
    *b = tmp;
}


