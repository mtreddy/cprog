#include<stdio.h>
#include<stdlib.h>
#include "../lock/sem_common.h"

void child_proc1(void)
{
  semid = semget(TEST_KEY, 2, 0777 | IPC_CREAT);
  if(semid < 0)
     printf("Could not get sem..!!\n");
  initarray[0] = initarray[1] = 1;
  semctl(semid, 2, SETALL, initarray);
  semctl(semid, 2, GETALL, outarray);
  printf(" Sem init vals %d %d\n", outarray[0], outarray[1]);
}

int main(int argc, char **argv)
{
        
    child_proc1();

    semid = semget(TEST_KEY, 2, 0777);
    if(semid < 0) {
     printf("Could not open sem..!!\n");
    }
    pbuf.sem_op = -1;
    pbuf.sem_flg = SEM_UNDO;
    vbuf.sem_op = 1;
    vbuf.sem_flg = SEM_UNDO;

    pbuf.sem_num = 1;
    if(semop(semid, &pbuf,1) < 0) 
        printf("1 Could not get sem\n");
    printf("Going to sleep 5sec\n");
    sleep(5);
    printf("out of  sleep\n");
    pbuf.sem_num = 0;
    if(semop(semid, &pbuf,1) < 0) 
        printf("2 Could not get sem\n");
    vbuf.sem_num = 1;
    if(semop(semid, &vbuf,1) < 0) 
        printf("3 Could not get sem\n");
    printf("Going to sleep 5sec\n");
    sleep(5);
    printf("out of  sleep\n");
    vbuf.sem_num  = 0;
    if(semop(semid, &vbuf,1) < 0) 
        printf("4 Could not get sem\n");

}
