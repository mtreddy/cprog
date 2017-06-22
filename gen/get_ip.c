#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int validate_ip_addr(char *ip)
{
    char str[50];
    char   *ptr = NULL;
    int val;

    strcpy(str, ip);

        ptr = strtok(str, ".");
    if(ptr == NULL)
        return -1;
    val = strtoul(ptr, NULL, 0);
    if(val == 0)
        return -1;

    ptr = strtok(NULL, ".");
    if(ptr == NULL)
        return -1;
    val = strtoul(ptr, NULL, 0);
    if(val == 0)
        return -1;
    ptr = strtok(NULL, ".");

    if(ptr == NULL)
        return -1;
    val = strtoul(ptr, NULL, 0);
    if(val == 0)
        return -1;

    return 0;
}
void get_ip_addr(char *istr)
{
    int rc = 0;
    FILE *file;
    char str[100];
    char str1[100];
    char *ptr, *ptr1;
    char delim[] = " :";

    rc = system("ifconfig eth0 > /tmp/ethaddr.txt");
    file = fopen("/tmp/ethaddr.txt", "r");

    while(!feof(file)) {
        fgets(str, 100, file);
        ptr = strstr(str, "inet addr");
        if(ptr != NULL) {
            strcpy(str1, ptr);
            ptr = strtok(str1, delim);
            if(ptr != NULL)
                ptr = strtok(NULL, delim);
            else
                break;
            if(ptr != NULL)
                ptr = strtok(NULL, delim);
            else
                break;
            printf("--%s--\n", ptr);
            strcpy(istr, ptr);
        }
    }
    fclose(file);

}
int analyze_trf(void)
{
    int rc = 0;
    FILE *file;
    char str[100];
    char str1[100];
    char *ptr, *ptr1;
    char delim[] = " :";
    int txpkts = 0, rxpkts = 0;

    file = fopen("/tmp/get_trf.txt", "r");
    if(file == NULL)
        return -1;
    while(!feof(file)) {
        fgets(str, 100, file);
        ptr = strstr(str, "sent");
        if(ptr != NULL) {
            strcpy(str1, ptr);
            ptr = strtok(str1, delim);
            if(ptr != NULL)
                ptr = strtok(NULL, delim);
            else
                break;
            txpkts = strtoul(ptr,NULL,0);
        }
    }
    fclose(file);

    file = fopen("/tmp/get_trf.txt", "r");
    while(!feof(file)) {
        fgets(str, 100, file);
        ptr = strstr(str, "Rcvd");
        if(ptr != NULL) {
            strcpy(str1, ptr);
            ptr = strtok(str1, delim);
            if(ptr != NULL)
                ptr = strtok(NULL, delim);
            else
                break;
            rxpkts = strtoul(ptr,NULL,0);
        }
    }
    fclose(file);
    if(rxpkts == txpkts) {
        printf("PASSED: RX packets equal to Tx pkts\n");
        rc = 0;
    }
    else {
        printf("ERRORK RX packets NOT equal to Tx pkts\n");
        rc = -1;
    }


    return rc;
}
int main(void)
{
    char str[20], str1[20];
    char trf_str[100];
    char delim[] = ".";
    char *ptr = NULL;
    int i = 0, j = 0;

    get_ip_addr(str);
    int ret = validate_ip_addr(str);
    if(ret) {
        printf("Failed to get ip address. Test failed...!!");
        return -1;
    }
    printf("IPADDR %s\n",str);
    /*Now modify the address to ping the gate way*/
    while(str[i++] != '\0') {
        if(str[i] == '.')
            j++;
        if(j == 3) {
            str[i+1] = '1';
            str[i+2] = '\0';
            break;
        }
    }

    printf("GateWay IP: %s\n",str);
    

//    sprintf("ping %s -e eth0 -c 10 > /tmp/get_trf.txt", str);
//    system(trf_str);
    if(analyze_trf()) 
        printf("TRAFFIC test Failed\n");
}

