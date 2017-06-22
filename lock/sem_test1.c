#include "sem_common.h"

int main(void)
{
    int ret = 0;
    int semid = 0;


    if((semid = sem_init()) < 0) {
        printf("Seminit failed\n");
        exit(1);
    }
    printf("semid = %d\n", semid);
    if(sem_lock(semid) < 0) {
        printf("Semlock failed\n");
        exit(1);
    }
    printf("locked\n");
    sleep(10);
    if(sem_unlock(semid) < 0) {
        printf("Sem unlock failed\n");
        exit(1);
    }
    printf("un-locked\n");
}
