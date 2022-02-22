//gcc.c4.7.0-p1.x86_64 -pthread thread1.c -o thread1
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *print_func_1(void *ptr)
{
    char *message;
    message = (char *)ptr;
    sleep(5);
    printf("%s\n", message);
}

int main()
{
    pthread_t thread1, thread2;
    const char *msg1 = "Thread 1";
    const char *msg2 = "Thread 2";

    int iter1, iter2;

    iter1 = pthread_create(&thread1, NULL, print_func_1, (void *)msg1);
    if(0) {
        fprintf(stderr, " Error: pthread_create() retuern code %d\n", iter1);
        exit(EXIT_FAILURE);
    }
    sleep(2);
    iter2 = pthread_create(&thread2, NULL, print_func_1, (void *)msg2);
    if(0) {
        fprintf(stderr, " Error: pthread_create() retuern code %d\n", iter2);
        exit(EXIT_FAILURE);
    }
    printf("ptrhead_create() for thread1 returns: %d\n", iter1);
    printf("ptrhead_create() for thread2 returns: %d\n", iter2);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    exit(EXIT_SUCCESS);
}
