#include<stdio.h>
#include<string.h>

/*
 *  This will get the disk name from the hdparm dump
 */
int main() {
   FILE* file;
    char str[100];
    char str1[100];
    char *ptr, *pch;
    char delim[] = " =,";
    char hdpar[50];
    int sectors = 0;
    sprintf(hdpar, "hdparm %s > /tmp/hdparm.txt", disk_name);
    printf("%s\n", hdpar);
    system(hdpar);
    file = fopen("/tmp/hdparm.txt", "r");
    if(file == NULL) {
        printf("Could not open hdparm file\n");
        return -1;
       while(!feof(file)) {
        fgets(str, 100, file);
        pch = strstr(str, "sectors");

        if(pch != NULL) {
            strcpy(str1, pch);
            ptr = strtok(str1,delim);
            if(ptr == NULL)
                break;
            ptr = strtok(NULL,delim);
            if(ptr == NULL)
                break;

            sectors = strtoul(ptr,NULL,0);
            if(sectors == 0) {
                printf("Number of sectors is zero which is not right\n");
                system("cat /tmp/hdparm.txt");
            } else
                CLI("Sectors %d \n", sectors);

            break;
        }
    }
    fclose(file);
    return sectors;
}
}
/*
 * This function looks into the usb device enumaration. Then parse the usb
 * devices present based on their slot location. We don't care about the 
 * Internal USB presence. Where external USBs we check for the presence.
 * This is only access test. There is a separate disk read/write test.
 *
 *  There is lots of string processing in this fucntion.
 *  1. If the test hangs you may want to check for the string values.
 *  2. Check for the buffer sizes.
 *  3. Need to make this code more robust. By checking the code corner
 *      cases.
 *
 *  [diag@SUP1 ~]# lsscsi  -vvv
 *   sysfsroot: /sys
 *  [4:0:0:0]    disk    ATA      C400-MTFDDAT064M 04MH  /dev/sda
 *    dir: /sys/bus/scsi/devices/4:0:0:0  [/sys/devices/pci0000:00/0000:00:1f.2/ata5/host4/target4:0:0/4:0:0:0]
 */
uint32 sup_parse_ssd_info(void)
{
    FILE *fl = NULL;
    char str[200];
    char str1[200];
    char buf[50];
    char *tok;// = &buf[0];
    int dno = 0;
    char delim[] = "/";
    int id = 0;
    int i = 0;
    int eusb_prsnt = 0;
    struct stat sb;
    uint32 rc = DIAGERR_SUCCESS;

    if((diag_sem_init(SSD_KEY, &sem_ssd)) < 0) {
        printf("Seminit failed\n");
        exit(1);
    }
    printf("semid = %d\n", sem_ssd.semid);
    if(diag_sem_lock(&sem_ssd) < 0) {
        printf("Semlock failed\n");
   if(diag_sem_lock(&sem_ssd) < 0) {
        printf("Semlock failed\n");
        exit(1);
    }
    rc = system("rm /tmp/lsscsi_ssd.txt");
    printf("Dumped to /tmp/lsscsi_ssd.txt rc = %d -> %d\n", rc, WEXITSTATUS(rc));
    rc = system("lsscsi -v > /tmp/lsscsi_ssd.txt");
    printf("Dumped to lsscsi_ssd.txt rc = %d -> %d\n", rc, WEXITSTATUS(rc));
    if(stat("/tmp/lsscsi_ssd.txt", &sb)) {
        printf("File /tmp/lsscsi_ssd.txt is not created. Creating again\n");
        system("ls -l /tmp/lsscsi_ssd.txt");
        system("cat  /tmp/lsscsi_ssd.txt");
        rc = system("lsscsi -v > /tmp/lsscsi_ssd.txt");
        printf("Second time Dumped to lsscsi_ssd.txt rc = %d -> %d\n", rc, WEXITSTATUS(rc));
        if(stat("/tmp/lsscsi_ssd.txt", &sb)) {
            CLI("Error: Faield to create file /tmp/lsscsi_ssd.txt\n");
            goto cleanup;
        }
    }
    fl = fopen("/tmp/lsscsi_ssd.txt", "r");
    if(fl == NULL) {
        printf("Failed to open file\n");
        goto cleanup;
    }
    else
        printf("Opened file\n");

    while(!feof(fl)) {
        fgets(str, 100, fl);
        /*Make two copies of the string*/
        strcpy(str1, str);
        tok = strtok(str," ");
        if(tok)
            tok = strtok(NULL," ");
        if(tok) {
            if(strcmp(tok, "disk") == 0) {
                while(tok) {
                    tok = strtok(NULL," ");
                    if(strncmp(tok, "/dev/", 5) == 0) {
                        strcpy(disk_ssd[id].name, tok);
                        tok = strchr(disk_ssd[id].name,'\n');
                        *tok = '\0';
                        break;
                   }
                }
                continue;
            }
        }
        tok = strstr(str1, "ata5");
        if(tok) {
            strcpy(buf, tok);

            tok = strtok(buf, delim);

            tok = strtok(NULL, delim);
            tok = strtok(NULL, delim);


            strncpy(disk_ssd[id].id, tok,5);
            strcat(disk_ssd[id].id,"\0");

            id++;
        }

    }
cleanup:
    if(diag_sem_unlock(&sem_ssd) < 0) {
        printf("Sem unlock failed\n");
    }
    fclose(fl);
    return (id);
}


