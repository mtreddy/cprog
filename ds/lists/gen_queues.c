#include <stdio.h>
#include "gen_llist.h"

/*
 * Add element at the end of the queue
 */
int queue_enqueue(list *queue, void *data)
{
    list_ins_next(queue, list_tail(queue), data);
}
/*
 * remove element from the front  of the queue
 */
int queue_dequeue(list *queue,  void **data)
{
    list_rem_next(queue, NULL, data);
}
int main(void)
{
    return 0;
}
