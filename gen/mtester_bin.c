#include <stdio.h>

int main(int argc, char** argv)
{
    //char bpath[] = "/home/mareddy/workspace/tree0105/x86-base/usr/bin/memtester";
    char bpath[] = "./memtester";
    char bbpath[100];
    int err;


    sprintf(bbpath,"%s %s \n","ls", bpath);
    printf("%s\n",bbpath);
    if(system(bbpath) != 0) {
        printf("File %s not present\n",bpath);
        return -1;
    }
    //sprintf(bbpath,"%s %s %s %s %s \n",bpath, "-p", argv[1], argv[2], argv[3]);
    sprintf(bbpath,"%s %s %s %s \n",bpath, "-f", argv[1],argv[2]);
    printf("%s\n",bbpath);
#if 0

    if(system("/home/mareddy/workspace/tree0105/x86-base/usr/bin/memtester 64k 1") == 0) 
        printf("Mem test was successfull\n");
    else
        printf("Mem test was Faield\n");
    if(system("/home/mareddy/workspace/tree0105/x86-base/usr/bin/memtester -p 0x1000000 64k 1") == 0) 
        printf("Mem test was successfull\n");
    else
        printf("Mem test was Faield\n");
#else
    err = system(bbpath);
    if( err  == 0) 
        printf("Mem test was successfull\n");
    else
        printf("Mem test was Faield err = %d \n", err);
#endif
    return err;
}
