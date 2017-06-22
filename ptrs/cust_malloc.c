#include<stdio.h>
#include <malloc.h>

/*Warpper to return  */
void *amalloc(int size); //return integer aligned pointer
void afree(void *ptr);
/**/
void *amalloc(int size)
{
  void *tmp;
  unsigned long tmp1 = 0;
  /*use malloc*/
  /* at least 8+size bytes allcoated*/
  tmp = (void*)malloc(size - size%sizeof(int)+2 * sizeof(int));
  /*size + 8 */
  tmp1 = (unsigned long)tmp;
  /*size + aligned lower bound, */
  tmp1 = tmp1  + sizeof(int);
  /*save ptr tmp to be able to free  */
  *(unsigned long *)tmp = (unsigned long )tmp; 
  return (void *)(tmp1);
 
}
/*
 *  7bytes , 7+8 ==15 , aligned 8.
 *  
 */
void afree(void *ptr)
{
  void *tmp;
  unsigned long tmp1 = 0;
  tmp1 = ((unsigned long )ptr);
  tmp1 = ((unsigned long )ptr-sizeof(int));
  printf("*tmp1%x\n", *(unsigned long*)tmp1);
  if(tmp1 != 0) 
    free( (void *)(*(unsigned long *)tmp1));
}

int main()
{
    void * tmp;
    unsigned long  tmp1;
    tmp = amalloc(5); 
    tmp1 = (unsigned long )tmp;
    printf("tmpx%x\n", tmp);
    printf("tmpx%x\n", tmp);
    printf("tmp1%x\n", tmp1);
    afree(tmp);
}

