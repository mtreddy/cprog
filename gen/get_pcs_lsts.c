#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int get_gw_ip(void)
{
    int rc = 0;
    FILE *file;
    char str[100];
    char str1[100];
    char *ptr, *ptr1;
    char delim[] = " ";
    int tx_errors = 0, tx_drops = 0, rx_errors, rx_drops = 0;
    int gw_found = 0, rcvd_found = 0;
    unsigned int val = 0;

    rc = system("ethtool -d eth0 | grep PCS_LSTS > /tmp/PCS_LSTS.txt");
    file = fopen("/tmp/PCS_LSTS.txt", "r");
    if(file == NULL)
        return -1;
    while(!feof(file)) {
        fgets(str, 100, file);
        ptr = strstr(str, "PCS_LSTS");
        if(ptr != NULL) {
            gw_found = 1;
            strcpy(str1, ptr);
            ptr = strtok(str1, delim);
            if(ptr != NULL)
            printf("1 %s\n", ptr);
            if(ptr != NULL)
                ptr = strtok(NULL, delim);
            else
                break;
            printf("1 %s\n", ptr);

            ptr = strtok(NULL, delim);
            if(ptr == NULL)
                break;
            printf("1 %s\n", ptr);
            ptr = strtok(NULL, delim);
            if(ptr == NULL)
                break;
            printf("1 %s\n", ptr);
            ptr = strtok(NULL, delim);
            if(ptr == NULL)
                break;
            printf("2 %s\n", ptr);
            sscanf(ptr, "0x%x", &val);
            printf("val=0x%x\n", val);
        }
    }
    fclose(file);
}
int main()
{
    get_gw_ip();
}
