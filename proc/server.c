/*
 * Create pool of threads.
 *  Handle events by one thread.
 *  Handle process monitoring by one thread
 *  Data handling by one thread.
 */
#include <stdio.h>
#include <sys/pthreads.h>
int pids[10];
int main(int argc, char **argv)
{
   for(int i = 0; i < 10; i++) {
       pids[i] = pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg)
   }
}
