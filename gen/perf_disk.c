#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h> 
#include <sys/stat.h> 


int main(void)
{
    char str[100];
    char str1[100];
    FILE *file;
    char *ptr = NULL;
    char delim[] = "=, ";
    int rc = 0;
    struct stat sb;

    if(stat("/mnt_ssd_bw", &sb)) {
        rc = system("mkdir /mnt_ssd_bw");
        if((rc != 0) && stat("/mnt_ssd_bw", &sb)) {
            printf("Failed to create mnt point /mnt_ssd_bw rc = %d WEXITSTATUS(%d) = %d \n", rc, rc, WEXITSTATUS(rc)); 
            return rc;
        }
    } else {
        printf("/mnt_ssd_bw already present. Let us un-mount just to be sure.\n");
        rc = system("umount /mnt_ssd_bw");
        if(rc)
        printf("Could not umount /dev/sda4 may be not mounted rc %d WEXITSTATUS(%d) = %d\n", rc, rc, WEXITSTATUS(rc));
        
    }

    rc = system("mount /dev/sda3 /mnt_ssd_bw");
    if(rc != 0) {
        printf("Could not mount /dev/sda3 on /mnt_ssd_bw rc %d WEXITSTATUS(%d) = %d\n", rc, rc, WEXITSTATUS(rc));
        return rc;
    } else 
        printf("mounted /dev/sda3 on /mnt_ssd_bw\n");

#if 0
    rc = system("/diag/bin/fio /diag/etc/conf/rand_wr.fio > /tmp/rand_wr.txt");
    printf("FIO check rc = %d -> %d\n", rc, WEXITSTATUS(rc)); 
#endif
    file = fopen("/tmp/rand_wr.txt", "r");

    while(!feof(file)) {
        fgets(str, 100, file);
        ptr = strstr(str, "runt");
        if(ptr != NULL) {
            ptr = strstr(str, "bw");
            if(ptr == NULL) continue;
            strcpy(str1, ptr);
           ptr = strtok(str1, delim); 
           if(ptr != NULL ) ptr  = strtok(NULL, delim); 
           else continue;
           if(ptr != NULL ) {
               int val ;
               sscanf(ptr, "%dKB/s", &val);
               if(val == 0 ) {
                    sscanf(ptr, "%dMB/s", &val);
                    if(val == 0) {
                        printf("BW:  %s\n", ptr);
                        printf("BW is not valid. Something is not right\n");
                        return -1;
                    }
               }
               printf("BandWidth:  %s\n", ptr);
           }
           else continue;
           ptr = strstr(str, "iops");
            if(ptr != NULL) {
               strcpy(str1, ptr);
               ptr = strtok(str1, delim); 
               if(ptr != NULL ) ptr  = strtok(NULL, delim); 
                else continue;
               if(ptr != NULL ) printf("IOPs:   %s\n", ptr);
                else continue;
               continue;
            }
           continue;
        }
        ptr = strstr(str, "usr");
        if(ptr != NULL) {
           printf("Utilization:%s\n", ptr);
        }

    }
    fclose(file);
    rc = system("umount /mnt_ssd_bw");
    if(rc != 0) { 
        printf("Could not umount /dev/sda4 on /mnt_ssd_bw rc %d WEXITSTATUS(%d) = %d\n", rc, rc, WEXITSTATUS(rc));
        return rc; 
    } else             
        printf("un-mounted /dev/sda4 on /mnt_ssd_bw\n"); 
    rc = system("rmdir /mnt_ssd_bw/");
    return rc;
}
