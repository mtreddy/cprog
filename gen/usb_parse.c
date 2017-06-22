#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct disk_info {
    char id[10];
    char name[20];
};

int hdp_check(char disk_name[])
{
    
    FILE* file;
    char str[100];
    char str1[100];
    char *ptr, *pch;
    char delim[] = " =,";
    char hdpar[25]; 
    int sectors = 0;

    sprintf(hdpar, "hdparm %s > hdparm.txt", disk_name); 
//    printf("%s\n", hdpar);
    system(hdpar);
    file = fopen("hdparm.txt", "r");
    if(file == NULL) {
        printf("Could not ioen hdparm file\n");
        return -1;
    }
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
            if(sectors == 0)
                printf("Number of sectros is zero which is not right\n");
            else
                printf("sectors %d \n", sectors);

            break;
        }
    }
    fclose(file);
    return sectors;
}
int main(int argc, char* argv)
{
    int rc = 0 ;
    FILE *fl = NULL;
    char str[200];
    char str1[200];
    char buf[50];
    struct disk_info disk_in[3];
    char *tok;// = &buf[0];
    int dno = 0;
    char delim[] = "/";
    int id = 0;
    int i = 0;
    int dprsnt[3] = {0, 0, 0};

    rc = system("rc ./lsscsi.txt");
    printf("Dumped to lsscsi.txt rc = %d -> %d\n", rc, WEXITSTATUS(rc)); 
    rc = system("lsscsi -v > ./lsscsi.txt");
    printf("Dumped to lsscsi.txt rc = %d -> %d\n", rc, WEXITSTATUS(rc)); 
    fl = fopen("./lsscsi.txt", "r");
    if(fl == NULL) {
        printf("Failed to open file\n");
        return -1;
    }
    else
        printf("Opened file\n");
    
    while(!feof(fl)) {
        fgets(str, 100, fl);
        /*Make two copies of the string*/
        strcpy(str1, str);
        tok = strtok(str," ");
        if(tok) {
            tok = strtok(NULL," ");
        }

        if(tok) {
            if(strcmp(tok, "disk") == 0) {
                while(tok) {
                    tok = strtok(NULL," ");
                    if(strncmp(tok, "/dev/", 5) == 0) {
                        strcpy(disk_in[id].name, tok);
                        tok = strchr(disk_in[id].name,'\n');
                        *tok = '\0';
                        break;
                    }
                }
                continue;
            }
        }

        tok = strstr(str1, "usb1");
        if(tok) {
            strcpy(buf, tok);

            tok = strtok(buf, delim);

            tok = strtok(NULL, delim);
            tok = strtok(NULL, delim);


            strcpy(disk_in[id].id, tok);
            id++;
        }

    }

    for(i = 0 ; i < 3; i++) {
        if(strcmp(disk_in[i].id,"1-1.1" ) == 0) {
            printf("Internal USB disk present:%s ",disk_in[i].name);
            hdp_check(disk_in[i].name);
            dprsnt[0] = 1;
        } else if(strcmp(disk_in[i].id,"1-1.5" ) == 0) {
            printf("Top slot USB disk present ");
            hdp_check(disk_in[i].name);
            dprsnt[1] = 1;
        } else if(strcmp(disk_in[i].id,"1-1.6" ) == 0) {
            printf("Bottom slot USB disk present ");
            hdp_check(disk_in[i].name);
            dprsnt[2] = 1;
        }

    }
    if(!dprsnt[0]) {
            printf("ERR:Internal USB disk NOT present\n");
            //rc = -1;
    }
    if(!dprsnt[1]) {
            printf("ERR: Top slot USB disk NOT present\n");
            rc = -1;
    }
    if(!dprsnt[2]) {
            printf("ERR:Bottom slot USB disk NOT present\n");
            rc = -1;
    }
    fclose(fl);
    return rc;
}
