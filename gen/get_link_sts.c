#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main(void)
{
    char cmd[100];
    char intf[50] = "eth1";
    char fname[50];
    char delim[] = "link ok";
    char *ptr = NULL;
    FILE *fp = NULL;
    int rc = 0;

    sprintf(fname, "/tmp/link_%s.txt", intf);
    printf("fname=%s\n", fname);
    sprintf(cmd, "mii-tool %s > %s", intf, fname);
    printf("cmd=%s\n", cmd);
    rc = system(intf);
    printf("rc = %d WEXITSTATUS(rc))=%d\n", rc, WEXITSTATUS(rc)); 
    fp = fopen(fname, "r");
    if(fp != NULL) {
        fgets(cmd, 100, fp);
        ptr = strstr(cmd, delim);
        printf("ptr=%s\n", ptr);
        printf("cmd=%s\n", cmd);
        if(ptr != NULL) {
            printf("Link is ok\n");
        } else {
            printf("Link not ok\n");
        }

    }
    
}
