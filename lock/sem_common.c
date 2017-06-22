#include "sem_common.h"
struct crit crti;


int sem_init(void)
{
    int semid = 0;
    int ret = 0;

    semid = semget(TEST_KEY, 2, 0777 | IPC_CREAT);
    if(semid < 0) {
        printf("semget failed..\n");
        exit(1);
    }
    ret = semctl(semid, 2, GETALL, outarray);
    if(outarray[0] == 1) {
        printf("Already intialized..\n");
        return 0;
    }
    initarray[0] = initarray[1] = 1;
    ret = semctl(semid, 2, SETALL, initarray);
    if(ret < 0) {
        printf("semctl failed..\n");
        return ret;
    }
    ret = semctl(semid, 2, GETALL, outarray);
    if(ret < 0) {
        printf("semctl failed..\n");
        return ret;
    }
    printf(" Sem init vals %d %d\n", outarray[0], outarray[1]);
    if(ret == 0)
        return semid;
    else
        return ret;
}

int sem_lock(int semid)
{
    int ret = 0;
    pbuf.sem_op = -1;
    pbuf.sem_num = 1;
    ret = semop(semid, &pbuf, 1);
    return ret;
}

int sem_unlock(int semid)
{
    int ret = 0;
    pbuf.sem_op = 1;
    pbuf.sem_num = 1;
    ret = semop(semid, &pbuf, 1);
    return ret;
}

void cleanup(int semid){
    
    semctl(semid, 2, IPC_RMID, 0);
    exit(1);
}


