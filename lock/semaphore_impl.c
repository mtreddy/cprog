#include<stdio.h>
#include<stdlib.h>

typedef struct call_block caller;
struct call_block{
    caller next;
    void *data;
    void (* fn) (void *);
};
typedef struct semaphore_t{
    //object obj;
    int value;
    caller queue;
}semaphore;
/*
 * Add at the end of te queue
 */
void t_queue(caller c, caller *queue)
{
    caller prev = NULL, q=*queue;
    while(q){
        prev = q;
        q = q->next;
    }
    if(prev == NULL) {
        *queue = c;
    } else {
      prev->next = c;
    }
    c->next = NULL
}
/*
 * Returns front of the queue
 */
caller t_dequeue( caller *queue)
{
    caller c = *queue;
    while(c){
        *queue = c->next;
    }
    return c;
}
void wait(semaphore *self, int c)
{
    caller wakeup = (caller)c;
    if(self->value > 0 ){
        self->value--;
        async(wakeup->obj, wakeup->meth, 0);
    } else {
        t_enqueue(c, &self->queue;
    }
}

void signal(semaphore *self, int unused)
{
    
    if(self->queue) {
        caller wakeup = t_dequeue((&self->queue);
        async(wakup->obj, wakeup->meth, 0);
    } else {
        self->value++;
    }
}

int init_sem(int n)
{
}
