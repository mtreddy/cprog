#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#include<sys/types.h>

#define futex system() { }
#define TEST_KEY 45678
int semid;
int count;
struct sembuf psembuf, vsembuf;
short initarray[2], outarray[2];
int first, second;

struct crit{
    int crit;
};

void cleanup(void)
{
    semctl(semid, 2, IPC_RMID, 0);
    exit(1);
}
void child_proc1(void)
{
    int i = 0;
    for(i =0; i < 20; i++)
        signal(i, cleanup);
  semid = semget(TEST_KEY, 2, 0777 | IPC_CREAT);
  initarray[0] = initarray[1] = 1;
  semctl(semid, 2, SETALL, initarray);
  semctl(semid, 2, GETALL, outarray);
  printf(" Sem init vals %d %d\n", outarray[0], outarray[1]);
  pause();
}
void child_proc2(int *first, int *second)
{

    *first = 0;
    *second = 1;
}
void child_proc3(int *first, int *second)
{

    *first = 1;
    *second = 0;
}

int main(int argc, char **argv)
{
    pid_t   child1, child2, child3, parent;

    parent = getpid();
    child1 = fork();
    child2 = fork();
    child3 = fork();
        
    if(child1 < 0) {
        printf("Could not fork child1..\n");
        return -1;
    }
    if(child2 < 0) {
        printf("Could not fork child2..\n");
        return -1;
    }
    if(child3 < 0) {
        printf("Could not fork child3..\n");
        return -1;
    }

    if(child1 == getpid()) {
        child_proc1();
    }else if(child2 == getpid()) {
        child_proc2(&first, &second);
    }else if(child3 == getpid()) {
        child_proc3(&first, &second);
    }

    semid = semget(TEST_KEY, 2, 0777);
    psembuf.sem_op = -1;
    psembuf.sem_flg = SEM_UNDO;
    vsembuf.sem_op = 1;
    vsembuf.sem_flg = SEM_UNDO;
    for(count = 0; ;count++) {
        psembuf.sem_num = first;
        semop(semid, &psembuf,1);
        psembuf.sem_num = second;
        semop(semid, &psembuf, 1);
        printf("Proc %d count %d\n", getpid(), count);
        vsembuf.sem_num=second;
        semop(semid, &vsembuf, 1);
        vsembuf.sem_num  = first;
        semop(semid, &vsembuf, 1);
    }
}
