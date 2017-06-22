#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>


int start_daemon_2(char **argv)
{
    pid_t p_id = 0;
    pid_t sid = 0;
    FILE *fp = NULL;

    /*Create child proc*/
    p_id = fork();

    if(p_id < 0) {
        printf("Failed to create child process\n");
        return -1;
    }

    if(p_id > 0) {
        printf("Parent process\n");
        return 0;
    }

    strcpy(argv[0], "child_daemon_2");
    umask(0);
    sid = setsid();
    if(sid < 0) {
        printf("Failed to creae SID\n");
       exit(1); 
    }

    /*
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    */

    fp = fopen("log1.txt", "w+");
    if(fp == NULL) exit(1);

    while(1) {
        sleep(1);
        fprintf(fp, "Loginrg ...\n");
        fflush(fp);
    }
    fclose(fp);
    return 0;

}
int start_daemon(char **argv)
{
    pid_t p_id = 0;
    pid_t sid = 0;
    FILE *fp = NULL;

    /*Create child proc*/
    p_id = fork();

    if(p_id < 0) {
        printf("Failed to create child process\n");
        return -1;
    }

    if(p_id > 0) {
        printf("Parent process\n");
        return 0;
    }

    strcpy(argv[0], "child_daemon_1");
    umask(0);
    sid = setsid();
    if(sid < 0) {
        printf("Failed to creae SID\n");
       exit(1); 
    }

    if(start_daemon_2(argv) == 0) {
        printf("started daemon succesfully\n");
    } else {

        printf("Failed to start daemon succesfully\n");
    }
    /*
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    */

    fp = fopen("log.txt", "w+");
    if(fp == NULL) exit(1);

    while(1) {
        sleep(1);
        fprintf(fp, "Loginrg ...\n");
        fflush(fp);
    }
    fclose(fp);
    return 0;

}

int main(int argc, char **argv)
{
    if(start_daemon(&argv[0]) == 0) {
        printf("started daemon succesfully\n");
    }
}
