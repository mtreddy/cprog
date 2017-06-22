/*
 *  gcc.c4.2.1-p4a.x86_64 -g3 shared_stack.c -o shared_stack
 * How can you implement n (n > 2) stacks in a single array, where no stack overflows until no space left in the entire array space?
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ARRAY_SIZE  100
int stack[ARRAY_SIZE];
int free_fr =ARRAY_SIZE;
int st1_ptr=0;
int st2_ptr=ARRAY_SIZE;
void push_st1(int val) {
    if(free_fr < 1) {
        printf("Error:stack ful...\n");
        return;    
    }
    printf("push ptr1=%d\n", st1_ptr);
   stack[st1_ptr] = val; 
   st1_ptr++;
    free_fr--;
}

int pop_st1(void) {
    free_fr++;
    st1_ptr--;
    printf("pop ptr1=%d\n", st1_ptr);
    return(stack[st1_ptr]);
}
void push_st2(int val) {
    if(free_fr < 1) {
        printf("Error:stack ful...\n");
        return;    
    }
   st2_ptr--;
   printf("push ptr2=%d\n", st2_ptr);
   stack[st2_ptr] = val; 
    free_fr--;
}

int pop_st2(void) {
    free_fr++;
    printf("pop ptr2=%d\n", st2_ptr);
    return(stack[st2_ptr++]);
}
int empty(void)
{
    if(free_fr == ARRAY_SIZE )
        return 0;
    else
        return 1;
}

int full(void)
{
    if(free_fr <=1 )
        return 0;
    else
        return 1;
}

main(){
    push_st1(1);
    push_st1(3);
    push_st1(5);
    push_st1(7);
    push_st2(11);
    push_st2(13);
    push_st2(15);
    push_st2(17);
    printf("%d\n",pop_st1());
    printf("%d\n",pop_st1());
    printf("%d\n",pop_st1());
    printf("%d\n",pop_st1());
    printf("%d\n",pop_st2());
    printf("%d\n",pop_st2());
    printf("%d\n",pop_st2());
    printf("%d\n",pop_st2());
    
}
