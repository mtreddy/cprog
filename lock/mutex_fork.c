#include "mutex_test.h"

int main(void)
{
    int cpid1, cpid2;
    lock_init(map);

    cpid1 = fork();
    if(cpid1 < 0) {
        printf("1 Caould not spawn child\n");
        exit(1);
    }
    cpid2 = fork();
    if(cpid2 < 0) {
        printf("2 Caould not spawn child\n");
        exit(1);
    }
    if(waitpid(cpid1, NULL, 0) == cpid1) {
        printf("Child1\n");
        test_lock(map);
        sleep(6);
        test_unlock(map);
    } 
    if(waitpid(cpid2, NULL, 0) == cpid2) {
        printf("Child2\n");
        test_lock(map);
        sleep(6);
        test_unlock(map);
    }
}
