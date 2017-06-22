#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int check_if_module_loaded(char* module)
{
    char str[50];
    char cmd_str[50];
    int size = 0;
    int usage = 0;
    int rc = 0;
    FILE *fp = NULL;
    sprintf(cmd_str, "lsmod | grep %s > /tmp/lsmod.txt", module);
    rc = system(cmd_str);
    printf("%s check rc = %d -> %d\n", __func__, rc, WEXITSTATUS(rc));
    fp =  fopen("/tmp/lsmod.txt", "r");
    if(fp == NULL) {
        printf("Failed to open lsmod.txt");
        return -1;
    }
    fscanf(fp, "%s %d %d", str, &size, &usage);
    printf( "module:%s \nsize:%d \nusage:%d\n", str, size, usage);
    fclose(fp);
    if(strcmp(module, str) == 0) {
        printf("Module %s already loaded\n", module);
    }
    else {
        printf("Module  %s is not  loaded\n", module);
        return 1;

    }
    if(usage != 0) {
        printf("ERROR: Module bing used by some one else\n");
        return -1;
    }

  return 0;
}
int main(void)
{
    if(check_if_module_loaded("diag_fpga") != 0) {
        printf("Issue checking if module opend\n");
    }
}
