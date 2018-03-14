#include "gen_stacks.h"

int stack_push(stack *stack, const void *data)
{
    return list_ins_next(stack, NULL, data);
}
int stack_pop(stack *stack, void **data)
{
    return list_rem_next(stack, NULL, data);
}
int main(void)
{
    return 0;
}
