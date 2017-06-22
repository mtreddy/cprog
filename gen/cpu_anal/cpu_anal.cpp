/*
 * Analyze CPU information
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>

#define create_new_pcie_db 1
#undef  create_new_pcie_db
struct cpu{
    int  snum;
    char vid[16];
    int  cpufam;
    char model[8];
    char mname[40];
    int  stepp;
    int  mccode;
    char mhz[8];
    char csize[8];
    int  phyid;
    int  siblings;
    int  coreid;
    int  numcores;
    int  apicid;
    int  ipicid;
    char fpu[4];
    char fpuexc[4];
    int  cpuidlvl;
    char wp[4];
    char flags[512];
    char bimips[8];
    int  cflush;
    int  calign;
    char asize[32];
    char pmgmt[4];
};

struct cpu_list{
    struct cpu cpu;
    struct cpu_list *next;
};

void cpu_list_add_node(struct cpu_list **head, struct cpu *cpu)
{
    struct cpu_list *tmp = *head;

    if(tmp == NULL) {
        tmp = (struct cpu_list *)malloc(sizeof(struct cpu_list));
        bcopy(cpu, &tmp->cpu, sizeof(struct cpu));
        tmp->next = NULL;
        *head = tmp;
        return;
    }
    while(tmp->next != NULL)
        tmp=tmp->next;

    tmp->next = (struct cpu_list *)malloc(sizeof(struct cpu_list));
    bcopy(cpu, &tmp->next->cpu, sizeof(struct cpu));
    tmp->next->next = NULL;
    return;
}
void cpu_list_dump(struct cpu_list *head)
{
    struct cpu_list *tmp = head;
    while(tmp != NULL) {
#if 1
        printf("cpu.snum; = %d\n", tmp->cpu.snum);
        printf("cpu.vid = %s\n", tmp->cpu.vid);
        printf("cpu.cpufam = %d\n", tmp->cpu.cpufam);
        printf("cpu.model = %s\n", tmp->cpu.model);
        printf("cpu.mname = %s\n", tmp->cpu.mname);
        printf("cpu.stepp = %d\n", tmp->cpu.stepp);
        printf("cpu.mccode = %d\n", tmp->cpu.mccode);
        printf("cpu.mhz = %s\n", tmp->cpu.mhz);
        printf("cpu.csize = %s\n", tmp->cpu.csize);
        printf("cpu.phyid = %d\n", tmp->cpu.phyid);
        printf("cpu.siblings = %d\n", tmp->cpu.siblings);
        printf("cpu.coreid = %d\n", tmp->cpu.coreid);
        printf("cpu.numcores = %d\n", tmp->cpu.numcores);
        printf("cpu.apicid = %d\n", tmp->cpu.apicid);
        printf("cpu.ipicid = %d\n", tmp->cpu.ipicid);
        printf("cpu.fpu = %s\n", tmp->cpu.fpu);
        printf("cpu.fpuexc = %s\n", tmp->cpu.fpuexc);
        printf("cpu.cpuidlvl = %d\n", tmp->cpu.cpuidlvl);
        printf("cpu.wp = %s\n", tmp->cpu.wp);
        printf("cpu.flags = %s\n", tmp->cpu.flags);
        printf("cpu.bimips = %s\n", tmp->cpu.bimips);
        printf("cpu.cflush = %d\n", tmp->cpu.cflush);
        printf("cpu.calign = %d\n", tmp->cpu.calign);
        printf("cpu.asize = %s\n", tmp->cpu.asize);
        printf("cpu.pmgmt = %s\n", tmp->cpu.pmgmt);
#endif
        tmp = tmp->next;
    }
}
int cpu_list_comp(struct cpu_list *old, struct cpu_list *new1)
{
    struct cpu_list *tmp1 = old;
    struct cpu_list *tmp2 = new1;
    int err = 0 ;
    if(tmp1 == NULL) {
        printf("ERROR: Data from file is NULL. ");
        return -1;
    }
    if(tmp2 == NULL) {
        printf("ERROR: Data from List is NULL. ");
        return -1;
    }
#if 1
    while((tmp2 != NULL) && (tmp1 != NULL)) {
        if(tmp2->cpu.snum != tmp1->cpu.snum){
            printf("Error: Serial numbers dont match exp %d got %d\n", tmp2->cpu.snum, tmp1->cpu.snum);
            err = 1;
        } 
        if(strcmp(tmp2->cpu.vid,tmp1->cpu.vid) != 0){
            printf("Error: Vendor_id doesnt match exp %s got %s\n", tmp2->cpu.vid , tmp1->cpu.vid);
            err = 1;
        } 
        if((tmp2->cpu.cpufam != tmp1->cpu.cpufam)){
            printf("Error: cpufam doesnt match exp %d got %d\n", tmp2->cpu.cpufam, tmp1->cpu.cpufam);
            err = 1;
        } 

        if(strcmp(tmp2->cpu.model,tmp1->cpu.model) != 0){
            printf("Error: model doesnt match exp %s got %s\n", tmp2->cpu.model, tmp1->cpu.model);
            err = 1;
        } 

        if(strcmp(tmp2->cpu.mname, tmp1->cpu.mname) != 0){
            printf("Error: Model name doesnt match exp %s got %s\n", tmp2->cpu.mname, tmp1->cpu.mname);
            err = 1;
        } 

        if((tmp2->cpu.stepp != tmp1->cpu.stepp) ){
            printf("Error: steppdoesnt match exp %d got %d\n", tmp2->cpu.stepp, tmp1->cpu.stepp);
            err = 1;
        } 

        if((tmp2->cpu.mccode !=  tmp1->cpu.mccode) ){
            printf("Warn: mccode doesnt match exp %d got %d\n", tmp2->cpu.mccode, tmp1->cpu.mccode);
        } 

        if(strcmp(tmp2->cpu.mhz, tmp1->cpu.mhz) != 0){
            printf("Warn: mhz doesnt match exp %s got %s\n", tmp2->cpu.mhz, tmp1->cpu.mhz);
        } 

        if(strcmp(tmp2->cpu.csize, tmp1->cpu.csize) != 0){
            printf("Error: csize doesnt match exp %s got %s\n", tmp2->cpu.csize, tmp1->cpu.csize);
            err = 1;
        } 

        if((tmp2->cpu.phyid !=  tmp1->cpu.phyid)) {
            printf("Error: phyid doesnt match exp %d got %d\n", tmp2->cpu.phyid, tmp1->cpu.phyid);
            err = 1;
        } 

        if((tmp2->cpu.siblings != tmp1->cpu.siblings) ){
            printf("Error: siblings doesnt match exp %d got %d\n", tmp2->cpu.siblings, tmp1->cpu.siblings);
            err = 1;
        } 

        if((tmp2->cpu.coreid != tmp1->cpu.coreid) ){
            printf("Error: coreid doesnt match exp %d got %d\n", tmp2->cpu.coreid, tmp1->cpu.coreid);
            err = 1;
        } 
        if((tmp2->cpu.numcores != tmp1->cpu.numcores) ){
            printf("Error: numcores doesnt match exp %d got %d\n", tmp2->cpu.numcores, tmp1->cpu.numcores);
            err = 1;
        } 

        if((tmp2->cpu.apicid != tmp1->cpu.apicid) ){
            printf("Warn: apicid doesnt match exp %d got %d\n", tmp2->cpu.apicid, tmp1->cpu.apicid);
        } 

        if((tmp2->cpu.ipicid != tmp1->cpu.ipicid) ){
            printf("Warn: ipicid doesnt match exp %d got %d\n", tmp2->cpu.ipicid, tmp1->cpu.ipicid);
        } 


        if(strcmp(tmp2->cpu.fpu,tmp1->cpu.fpu) != 0){
            printf("Error: Fpu doesnt match exp -%s- got -%s-\n", tmp2->cpu.fpu, tmp1->cpu.fpu);
            err = 1;
        } 

        if(strcmp(tmp2->cpu.fpuexc, tmp1->cpu.fpuexc) != 0){
            printf("Error:Fpuexc doesnt match exp -%s- got -%s-\n", tmp2->cpu.fpuexc, tmp1->cpu.fpuexc);
            err = 1;
        } 

        if((tmp2->cpu.cpuidlvl != tmp1->cpu.cpuidlvl) ){
            printf("Warn: cpuidlvl  doesnt match exp %d got %d\n", tmp2->cpu.cpuidlvl, tmp1->cpu.cpuidlvl);
        } 

        if(strcmp(tmp2->cpu.wp, tmp1->cpu.wp) != 0){
            printf("Warn: wp  doesnt match exp %s got %s \n", tmp2->cpu.wp, tmp1->cpu.wp);
        } 

        if(strcmp(tmp2->cpu.flags,tmp1->cpu.flags) != 0){
            printf("Warn:: flags  doesnt match exp %s got %s\n", tmp2->cpu.flags, tmp1->cpu.flags);
        } 

        if(strcmp(tmp2->cpu.bimips,tmp1->cpu.bimips) != 0){
            printf("Warn: bimips doesnt match exp %s got %s\n", tmp2->cpu.bimips, tmp1->cpu.bimips);
        } 

        if((tmp2->cpu.cflush != tmp1->cpu.cflush) ){
            printf("Error: cflush  doesnt match exp %d got %d\n", tmp2->cpu.cflush, tmp1->cpu.cflush);
            err = 1;
        } 

        if((tmp2->cpu.calign != tmp1->cpu.calign) ){
            printf("Error: calign  doesnt match exp %d got %d\n", tmp2->cpu.calign, tmp1->cpu.calign);
            err = 1;
        } 

        if(strcmp(tmp2->cpu.asize, tmp1->cpu.asize ) != 0){
            printf("Error: asize  doesnt match exp %s got %s\n", tmp2->cpu.asize, tmp1->cpu.asize);
            err = 1;
        } 

        tmp1 = tmp1->next;
        tmp2 = tmp2->next;
    }
#endif
    return err;
}
void cpu_list_free(struct cpu_list **head)
{
    struct cpu_list *tmp = *head, *tmp1;
    while(tmp != NULL) {
        tmp1 = tmp;
        tmp = tmp->next;
        //printf("Freeing node %d\n", tmp1->cpu.ser_num);
        free(tmp1);

    }
    *head = NULL;
}
int main(int argc, char **argv)
{
    unsigned int rc = 0;
    struct cpu_list *head = NULL;
    struct cpu_list *nhead = NULL;
    FILE *file, *db;
    char *ptr;
    char str[150], str1[100];
    char delim[] = ":";
    int val = 0;
    int pos = 0;
    struct cpu cpu;
    int generate = 0;
    
    //system("cat /proc/cpuinfo > /tmp/cpuinfo.txt");
    if(argc >= 2)
        if(strcmp(argv[1], "generate") == 0)
            generate = 1;

        file = fopen("/tmp/cpuinfo.txt","r");
    if(generate) {
        printf("generating file first time\n");
        bzero(&cpu, sizeof(struct cpu));
        /*
         * First time sup_lcpci.db will be created and copied
         * to source control. Every time there is change
         * this sup_lcpci.db need to be updated and copy to
         * source control where this test can find it.
         */
        /*Remove before you create*/
        system("rm /diag/bin/sup_cpuinfo.db");
        db = fopen("/diag/bin/sup_cpuinfo.db","w");
        while(!feof(file)) {
            fgets(str, 150, file);
            ptr = strtok(str,delim);
            if(ptr == NULL)
                continue;
                //printf("ptr --%s--\n", ptr);
            else if(strncmp("processor", ptr, 9) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    cpu.snum = strtoul(ptr, NULL, 0);
                    //printf("cpu.snum = %d\n", cpu.snum);
            }  else if(strncmp("vendor_id", ptr, 8) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    strcpy(str1, ptr);
                    ptr = strchr(str1,'\n');
                    *ptr = '\0';
                    strcpy(cpu.vid, str1);
                    //printf("cpu.vid= --%s--\n", cpu.vid);
            }  else if(strncmp("cpu family", ptr, 10) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    cpu.cpufam = strtoul(ptr, NULL, 0);
                    //printf("cpu.cpufam = %d\n", cpu.cpufam);
            }  else if(strncmp("model name", ptr, 10) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    strcpy(str1, ptr);
                    ptr = strchr(str1,'\n');
                    *ptr = '\0';
                    strcpy(cpu.mname, str1);
                    //printf("cpu.mname= --%s--\n", cpu.mname);
            }  else if(strncmp("model", ptr, 5) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    strcpy(str1, ptr);
                    ptr = strchr(str1,'\n');
                    *ptr = '\0';
                    strcpy(cpu.model, str1);
                    //printf("cpu.model = --%s--\n", cpu.model );
            }  else if(strncmp("stepping", ptr, 8) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    cpu.stepp= strtoul(ptr, NULL, 0);
                    //printf("cpu.stepp= %d\n", cpu.stepp);
            }  else if(strncmp("microcode", ptr, 9) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    cpu.mccode = strtoul(ptr, NULL, 0);
                    //printf("cpu.mccode= %d\n", cpu.mccode);
            }  else if(strncmp("cpu MHz", ptr, 7) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    strcpy(str1, ptr);
                    ptr = strchr(str1,'\n');
                    *ptr = '\0';
                    strcpy(cpu.mhz, str1);
                    //printf("cpu.mhz= --%s--\n", cpu.mhz);
            }  else if(strncmp("cache size", ptr, 9) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    strcpy(str1, ptr);
                    ptr = strchr(str1,'\n');
                    *ptr = '\0';
                    strcpy(cpu.csize, str1);
                    //printf("cpu.csize = --%s--\n", cpu.csize);
            }  else if(strncmp("physical id", ptr, 9) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    cpu.phyid = strtoul(ptr, NULL, 0);
                    //printf("cpu.phyid = %d\n", cpu.phyid );
            }  else if(strncmp("siblings", ptr, 7) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    cpu.siblings = strtoul(ptr, NULL, 0);
                    //printf("cpu.siblings = %d\n", cpu.siblings );
            }  else if(strncmp("core id", ptr, 7) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    cpu.coreid = strtoul(ptr, NULL, 0);
                    //printf("cpu.coreid = %d\n", cpu.coreid );
            }  else if(strncmp("cpu cores", ptr, 9) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    cpu.numcores = strtoul(ptr, NULL, 0);
                    //printf("cpu.numcores = %d\n", cpu.numcores );
            }  else if(strncmp("apicid", ptr, 6) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    cpu.apicid = strtoul(ptr, NULL, 0);
                    //printf("cpu.apicid = %d\n", cpu.apicid );
            }  else if(strncmp("initial apicid", ptr, 9) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    cpu.ipicid = strtoul(ptr, NULL, 0);
                    //printf("cpu.ipicid = %d\n", cpu.ipicid );
            }  else if(strncmp("fpu_exception", ptr, 9) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    strcpy(str1, ptr);
                    ptr = strchr(str1,'\n');
                    *ptr = '\0';
                    strcpy(cpu.fpuexc, str1);
                    //printf("cpu.fpuexc= --%s--\n", cpu.fpuexc);
            }  else if(strncmp("fpu", ptr, 3) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    strcpy(str1, ptr);
                    ptr = strchr(str1,'\n');
                    *ptr = '\0';
                    strcpy(cpu.fpu, str1);
                    //printf("cpu.fpu= --%s--\n", cpu.fpu);
            }  else if(strncmp("cpuid level", ptr, 9) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    cpu.cpuidlvl = strtoul(ptr, NULL, 0);
                    //printf("cpu.cpuidlvl= %d\n", cpu.cpuidlvl);
            }  else if(strncmp("wp", ptr, 2) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    strcpy(str1, ptr);
                    ptr = strchr(str1,'\n');
                    *ptr = '\0';
                    strcpy(cpu.wp, str1);
                    //printf("cpu.wp= %s\n", cpu.wp);
            }  else if(strncmp("flags", ptr, 5) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    //strcpy(str1, ptr);
                    //ptr = strchr(str1,'\n');
                    //*ptr = '\0';
                    strcpy(cpu.flags, ptr);
                    //printf("cpu.flags= %s\n", cpu.flags);
            }  else if(strncmp("bogomips", ptr, 7) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    strcpy(str1, ptr);
                    ptr = strchr(str1,'\n');
                    *ptr = '\0';
                    strcpy(cpu.bimips, str1);
                    //printf("cpu.bimips = %s\n", cpu.bimips);
            }  else if(strncmp("clflush size    ", ptr, 9) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    cpu.cflush= strtoul(ptr, NULL, 0);
                    //printf("cpu.cflush= %d\n", cpu.cflush);
            }  else if(strncmp("cache_alignment ", ptr, 9) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    cpu.calign = strtoul(ptr, NULL, 0);
                    //printf("cpu.calign = %d\n", cpu.calign );
            }  else if(strncmp("address sizes   ", ptr, 9) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    strcpy(str1, ptr);
                    ptr = strchr(str1,'\n');
                    *ptr = '\0';
                    strcpy(cpu.asize, str1);
                    //printf("cpu.asize= %s\n", cpu.asize);
            }  else if(strncmp("power management", ptr, 9) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    strcpy(str1, "Nothing");
                    strcpy(cpu.pmgmt, str1);
                    //printf("cpu.pmgmt= %s\n", cpu.pmgmt);
                    /* This is the last element in structure */
                    fwrite(&cpu, sizeof(struct cpu), 1, db);
                    fflush(db);
                    bzero(&cpu, sizeof(struct cpu));
            }
        }

        fclose(file);
        fclose(db);
        fflush(db);
        cpu_list_free(&head);
    } else {
        db = fopen("/diag/bin/sup_cpuinfo.db","r");
        printf("Reading from DB \n");
        bzero(&cpu, sizeof(struct cpu));
        /* Build list from DB file */
        while(fread(&cpu, sizeof(struct cpu), 1, db) == 1) {
            cpu_list_add_node(&head, &cpu);
            fflush(db);
        }
        fclose(db);
        /*Build list from current /tmp/cpuinfo.txt file*/

        while(!feof(file)) {
            fgets(str, 150, file);
            ptr = strtok(str,delim);
            if(ptr == NULL)
                continue;
                //printf("ptr --%s--\n", ptr);
            else if(strncmp("processor", ptr, 9) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    cpu.snum = strtoul(ptr, NULL, 0);
                    //printf("cpu.snum = %d\n", cpu.snum);
            }  else if(strncmp("vendor_id", ptr, 8) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    strcpy(str1, ptr);
                    ptr = strchr(str1,'\n');
                    *ptr = '\0';
                    strcpy(cpu.vid, str1);
                    //printf("cpu.vid= --%s--\n", cpu.vid);
            }  else if(strncmp("cpu family", ptr, 10) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    cpu.cpufam = strtoul(ptr, NULL, 0);
                    //printf("cpu.cpufam = %d\n", cpu.cpufam);
            }  else if(strncmp("model name", ptr, 10) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    strcpy(str1, ptr);
                    ptr = strchr(str1,'\n');
                    *ptr = '\0';
                    strcpy(cpu.mname, str1);
                    //printf("cpu.mname= --%s--\n", cpu.mname);
            }  else if(strncmp("model", ptr, 5) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    strcpy(str1, ptr);
                    ptr = strchr(str1,'\n');
                    *ptr = '\0';
                    strcpy(cpu.model, str1);
                    //printf("cpu.model = --%s--\n", cpu.model );
            }  else if(strncmp("stepping", ptr, 8) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    cpu.stepp= strtoul(ptr, NULL, 0);
                    //printf("cpu.stepp= %d\n", cpu.stepp);
            }  else if(strncmp("microcode", ptr, 9) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    cpu.mccode = strtoul(ptr, NULL, 0);
                    //printf("cpu.mccode= %d\n", cpu.mccode);
            }  else if(strncmp("cpu MHz", ptr, 7) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    strcpy(str1, ptr);
                    ptr = strchr(str1,'\n');
                    *ptr = '\0';
                    strcpy(cpu.mhz, str1);
                    //printf("cpu.mhz= --%s--\n", cpu.mhz);
            }  else if(strncmp("cache size", ptr, 9) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    strcpy(str1, ptr);
                    ptr = strchr(str1,'\n');
                    *ptr = '\0';
                    strcpy(cpu.csize, str1);
                    //printf("cpu.csize = --%s--\n", cpu.csize);
            }  else if(strncmp("physical id", ptr, 9) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    cpu.phyid = strtoul(ptr, NULL, 0);
                    //printf("cpu.phyid = %d\n", cpu.phyid );
            }  else if(strncmp("siblings", ptr, 7) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    cpu.siblings = strtoul(ptr, NULL, 0);
                    //printf("cpu.siblings = %d\n", cpu.siblings );
            }  else if(strncmp("core id", ptr, 7) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    cpu.coreid = strtoul(ptr, NULL, 0);
                    //printf("cpu.coreid = %d\n", cpu.coreid );
            }  else if(strncmp("cpu cores", ptr, 9) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    cpu.numcores = strtoul(ptr, NULL, 0);
                    //printf("cpu.numcores = %d\n", cpu.numcores );
            }  else if(strncmp("apicid", ptr, 6) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    cpu.apicid = strtoul(ptr, NULL, 0);
                    //printf("cpu.apicid = %d\n", cpu.apicid );
            }  else if(strncmp("initial apicid", ptr, 9) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    cpu.ipicid = strtoul(ptr, NULL, 0);
                    //printf("cpu.ipicid = %d\n", cpu.ipicid );
            }  else if(strncmp("fpu_exception", ptr, 9) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    strcpy(str1, ptr);
                    ptr = strchr(str1,'\n');
                    *ptr = '\0';
                    strcpy(cpu.fpuexc, str1);
                    //printf("cpu.fpuexc= --%s--\n", cpu.fpuexc);
            }  else if(strncmp("fpu", ptr, 3) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    strcpy(str1, ptr);
                    ptr = strchr(str1,'\n');
                    *ptr = '\0';
                    strcpy(cpu.fpu, str1);
                    //printf("cpu.fpu= --%s--\n", cpu.fpu);
            }  else if(strncmp("cpuid level", ptr, 9) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    cpu.cpuidlvl = strtoul(ptr, NULL, 0);
                    //printf("cpu.cpuidlvl= %d\n", cpu.cpuidlvl);
            }  else if(strncmp("wp", ptr, 2) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    strcpy(str1, ptr);
                    ptr = strchr(str1,'\n');
                    *ptr = '\0';
                    strcpy(cpu.wp, str1);
                    //printf("cpu.wp= %s\n", cpu.wp);
            }  else if(strncmp("flags", ptr, 5) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    //strcpy(str1, ptr);
                    //ptr = strchr(str1,'\n');
                    //*ptr = '\0';
                    strcpy(cpu.flags, ptr);
                    //printf("cpu.flags= %s\n", cpu.flags);
            }  else if(strncmp("bogomips", ptr, 7) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    strcpy(str1, ptr);
                    ptr = strchr(str1,'\n');
                    *ptr = '\0';
                    strcpy(cpu.bimips, str1);
                    //printf("cpu.bimips = %s\n", cpu.bimips);
            }  else if(strncmp("clflush size    ", ptr, 9) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    cpu.cflush= strtoul(ptr, NULL, 0);
                    //printf("cpu.cflush= %d\n", cpu.cflush);
            }  else if(strncmp("cache_alignment ", ptr, 9) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    cpu.calign = strtoul(ptr, NULL, 0);
                    //printf("cpu.calign = %d\n", cpu.calign );
            }  else if(strncmp("address sizes   ", ptr, 9) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    strcpy(str1, ptr);
                    ptr = strchr(str1,'\n');
                    *ptr = '\0';
                    strcpy(cpu.asize, str1);
                    //printf("cpu.asize= %s\n", cpu.asize);
            }  else if(strncmp("power management", ptr, 9) == 0) {
                    //printf("ptr %s\n", ptr);
                    ptr = strtok(NULL,delim);
                    if(ptr == NULL)
                        continue;
                    strcpy(str1, "Nothing");
                    strcpy(cpu.pmgmt, str1);
                    //printf("cpu.pmgmt= %s\n", cpu.pmgmt);
                    /* This is the last element in structure */
                    cpu_list_add_node(&nhead, &cpu);
                    bzero(&cpu, sizeof(struct cpu));
            }
        }
        fclose(file);
        //cpu_list_dump(head);
        //cpu_list_dump(nhead);
        if(cpu_list_comp(head, nhead) == 0) {
            printf("CPU info test passed\n");
            rc = 0;
        } else {
            printf("CPU Info test Failed\n");
            rc = -1;
        }

        cpu_list_free(&head);
        cpu_list_free(&nhead);
    }
    return 0;
}
