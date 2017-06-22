#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int get_gw_ip(void)
{
    char intf[] = "eth1";
    char fname[] = "/diag/logs/route_eth1.txt";
    char istr[25];
    int rc = 0;
    FILE *file;
    char str[100];
    char str1[100];
    char *ptr, *ptr1;
    char cmd_str[100]; 
    char delim[] = " ";
    int tx_errors = 0, tx_drops = 0, rx_errors, rx_drops = 0;
    int gw_found = 0, rcvd_found = 0;
    sprintf(cmd_str, "/sbin/route -n | grep 'UG[ \t]' | awk '{print $2}' > /diag/logs/route_%s.txt", intf);
    rc = system(cmd_str);
    file = fopen(fname, "r");
    if(file == NULL) {
        printf("Faield to open file"); 
        return -1;
    }
    ptr1 = fgets(str, 100, file);
    if(ptr1 != NULL)
    {
        unsigned int ipstrlen = 0;
        gw_found = 1;
        ipstrlen = strlen(ptr1);
        ptr1[ipstrlen-1] = 0;
        printf("1 %s\n", ptr1);
        strcpy(istr, ptr1);
    }
#if 0
    while(!feof(file)) {
        fgets(str, 100, file);
        ptr = strstr(str, "default");
        if(ptr != NULL) {
            gw_found = 1;
            strcpy(str1, ptr);
            ptr = strtok(str1, delim);
            if(ptr != NULL)
                ptr = strtok(NULL, delim);
            else
                break;
            printf("1 %s\n", ptr);

            ptr = strtok(NULL, delim);
            if(ptr == NULL)
                break;
            printf("1 %s\n", ptr);
        }
    }
#endif
    fclose(file);
}
int main()
{
    get_gw_ip();
}
