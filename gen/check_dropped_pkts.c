#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int check_for_drop_erro_pkts(void)
{
    int rc = 0;
    FILE *file;
    char str[100];
    char str1[100];
    char *ptr, *ptr1;
    char delim[] = " :";
    int tx_errors = 0, tx_drops = 0, rx_errors, rx_drops = 0;
    int sent_found = 0, rcvd_found = 0;

    rc = system("ifconfig eth0 > ./ge_trf_ifcfg.txt");
    file = fopen("./ge_trf_ifcfg.txt", "r");
    if(file == NULL)
        return -1;
    while(!feof(file)) {
        fgets(str, 100, file);
        ptr = strstr(str, "TX packets");
        if(ptr != NULL) {
            sent_found = 1;
            strcpy(str1, ptr);
            ptr = strtok(str1, delim);
            if(ptr != NULL)
                ptr = strtok(NULL, delim);
            else
                break;

            ptr = strtok(NULL, delim);
            if(ptr == NULL)
                break;
            ptr = strtok(NULL, delim);
            if(ptr == NULL)
                break;
            ptr = strtok(NULL, delim);
            if(ptr == NULL)
                break;
            tx_errors = strtoul(ptr,NULL,0);
                
            ptr = strtok(NULL, delim);
            if(ptr == NULL)
                break;

            ptr = strtok(NULL, delim);
            if(ptr == NULL)
                break;
            tx_drops = strtoul(ptr,NULL,0);
            if(!tx_errors)
                sent_found = 0;
        }
    }
    fclose(file);
    file = fopen("./ge_trf_ifcfg.txt", "r");
    if(file == NULL)
        return -1;
    while(!feof(file)) {
        fgets(str, 100, file);
        ptr = strstr(str, "RX packets");
        if(ptr != NULL) {
            sent_found = 1;
            strcpy(str1, ptr);
            ptr = strtok(str1, delim);
            if(ptr != NULL)
                ptr = strtok(NULL, delim);
            else
                break;

            ptr = strtok(NULL, delim);
            if(ptr == NULL)
                break;
            ptr = strtok(NULL, delim);
            if(ptr == NULL)
                break;
            ptr = strtok(NULL, delim);
            if(ptr == NULL)
                break;
            rx_errors = strtoul(ptr,NULL,0);
                
            ptr = strtok(NULL, delim);
            if(ptr == NULL)
                break;

            ptr = strtok(NULL, delim);
            if(ptr == NULL)
                break;
            rx_drops = strtoul(ptr,NULL,0);
            if(!rx_errors)
                sent_found = 0;
        }
    }
    fclose(file);
    printf("tx_errors %d tx_drops %d rx_errors %d tx_drops %d\n", tx_errors, tx_drops, rx_errors, rx_drops);
}
int main()
{
    check_for_drop_erro_pkts();
}
