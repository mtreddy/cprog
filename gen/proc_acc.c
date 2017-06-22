#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BS 1024

void die(char *x){ perror(x); exit(1); };

int get_cpu_model(void);
int main(int argc, char **argv)
{
#if 0
    int n = 0;
    char    filepath[BS], buf[BS];
    FILE    *f = NULL;
    int     msize = 0;
    char *ptr = NULL;
    char delim[] = ":";
    
    //get the filename to open
        if(argc < 2){
                fprintf(stderr, "Usage: %s <proc file>\n", argv[0]);
        return 1;
    }
    
    //get the path of the file
    n = snprintf(filepath, BS-1, "/proc/%s", argv[1]);
    filepath[n] = 0;
    
    //open the file
    f = fopen(filepath, "r");
    if(!f)
        die("fopen");

    //print its contents
    while(fgets(buf, BS-1, f)) {
        if(strncmp(buf, "MemFree", 7) == 0) {
            ptr = strtok(buf, delim);
            if(ptr != NULL) {
                printf("%s \n", ptr);
                ptr = strtok(NULL, delim);
                printf("%s \n", ptr);
                msize = strtoul(ptr, NULL,0);
                printf("%d\n", msize);
            }
            break;
        }
    }
    if(ferror(f))
        die("fgets");
    fclose(f);

    return 0;
#else
    int model = get_cpu_model();
    printf("CPU model is %d\n", model);
#endif
}
int get_cpu_model(void) 
{
    int n = 0;
    char    buf[BS];
    FILE    *f = NULL;
    int     model = 0;
    char *ptr = NULL;
    char delim[] = ":";
    
    //open the file
    f = fopen("/proc/cpuinfo", "r");
    if(!f)
        die("fopen");

    //print its contents
    while(fgets(buf, BS-1, f)) {
        if(strncmp(buf, "model", 5) == 0) {
            ptr = strtok(buf, delim);
            if(ptr != NULL) {
                printf("%s \n", ptr);
                ptr = strtok(NULL, delim);
                printf("%s \n", ptr);
                model = strtoul(ptr, NULL,0);
                printf("%d\n", model);
            }
            break;
        }
    }
    if(ferror(f))
        die("fgets");
    fclose(f);

    return model;
}
