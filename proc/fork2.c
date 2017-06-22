#include<stdio.h>
#include<stdlib.h>
#include "../lock/sem_common.h"

int main(int argc, char **argv)
{

    semid = semget(TEST_KEY, 2, 0777);
    if(semid < 0) {
     printf("Could not open sem..!!\n");
    }
    pbuf.sem_op = -1;
    pbuf.sem_flg = SEM_UNDO;
    vbuf.sem_op = 1;
    vbuf.sem_flg = SEM_UNDO;

    pbuf.sem_num = -1;
    if(semop(semid, &pbuf,1) < 0)
        printf("1 semop failed\n");
    pbuf.sem_num = 0;
    if(semop(semid, &pbuf,1) < 0)
        printf("2 semop failed\n");
    vbuf.sem_num = 1;
    if(semop(semid, &vbuf,1) < 0)
        printf("3 semop failed\n");
    vbuf.sem_num  = 0;
    semop(semid, &vbuf, 1);
    if(semop(semid, &vbuf,1) < 0)
        printf("4 semop failed\n");
    printf("Fork2 Going to sleep 10sec\n");
    printf("fork2 out of  sleep\n");

}
