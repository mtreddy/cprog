#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>

//#define CREATE_NEW_PCIE_DB 1
#undef  CREATE_NEW_PCIE_DB
struct device{
    int ser_num;
    char bus[10];
    char fun[20];
    char name[100];
};

struct dev_list{
    struct device dev;
    struct dev_list *next;
};

void dev_list_add_node(struct dev_list **head, struct device *dev)
{
    struct dev_list *tmp = *head;

    if(tmp == NULL) {
        tmp = (struct dev_list *)malloc(sizeof(struct dev_list));
        bcopy(dev, &tmp->dev, sizeof(struct device));
        tmp->next = NULL;
        *head = tmp;
        return;
    }
    while(tmp->next != NULL)
        tmp=tmp->next;

    tmp->next = (struct dev_list *)malloc(sizeof(struct dev_list));
    bcopy(dev, &tmp->next->dev, sizeof(struct device));
    tmp->next->next = NULL;
    return;
}
void dev_list_dump(struct dev_list *head)
{
    struct dev_list *tmp = head;
    while(tmp != NULL) {
        printf("dev.ser_num = %d\n", tmp->dev.ser_num);
        printf("dev.bus = %s\n", tmp->dev.bus);
        printf("dev.fun = %s\n", tmp->dev.fun);
        printf("dev.name= %s\n", tmp->dev.name);
        tmp = tmp->next;
    }
}
int dev_list_comp(struct dev_list *old, struct dev_list *new)
{
    struct dev_list *tmp1 = old;
    struct dev_list *tmp2 = new;
    int err = 0 ;
    while((tmp2 != NULL) && (tmp1 != NULL)) {
        err = 0;
        if(tmp2->dev.ser_num == tmp1->dev.ser_num){
            if(strcmp(tmp2->dev.bus, tmp1->dev.bus) != 0) {
                printf("Bus number doesn't match\n");
                err = 1;
            }
            if(strcmp(tmp2->dev.fun, tmp1->dev.fun) != 0) {
                printf("Functionality doesn't match\n");
                err = 1;
            }
            if(strcmp(tmp2->dev.name, tmp1->dev.name) != 0)
                printf("Name doesn't match\n");
            if(err) {
                printf("Exp dev.ser_num = %d dev.ser_num = %d \n", tmp1->dev.ser_num, tmp2->dev.ser_num);
                printf("Exp dev.bus = %s dev.bus = %s \n", tmp1->dev.bus, tmp2->dev.bus);
                printf("Exp dev.fun = %s dev.fun = %s \n", tmp1->dev.fun, tmp2->dev.fun);
                printf("Exp dev.name= %s ev.name= %s \n", tmp1->dev.name, tmp2->dev.name);
                return err;
            }
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        } else {
            printf("Serial numbers doesn't match\n");
            err = 1;
            return err;
        }
    }
}
void dev_list_free(struct dev_list **head)
{
    struct dev_list *tmp = *head, *tmp1;
    while(tmp != NULL) {
        tmp1 = tmp;
        tmp = tmp->next;
        //printf("Freeing node %d\n", tmp1->dev.ser_num);
        free(tmp1);

    }
    *head = NULL;
}
int main(int argc, char **argv)
{
    struct dev_list *head = NULL;
    struct dev_list *nhead = NULL;
    FILE *file, *db;
    char *ptr;
    char str[150], str1[100];
    char delim[] = " ";
    int val = 0;
    int pos = 0;
    struct device dev1;

    system("lspci > /tmp/lspci.txt");
#if defined(CREATE_NEW_PCIE_DB)
    bzero(&dev1, sizeof(struct device));
    dev1.ser_num = 0;
    file = fopen("/tmp/lspci.txt","r");
    /*
     * First time sup_lcpci.db will be created and copied
     * to source control. Every time there is change
     * this sup_lcpci.db need to be updated and copy to
     * source control where this test can find it.
     */
    /*Remove before you create*/
    system("rm /diag/bin/sup_lspci.db");
    db = fopen("/diag/bin/sup_lspci.db","w");
    while(!feof(file)) {
        fgets(str, 150, file);
        ptr = strtok(str,delim);
        if(ptr == NULL)
            continue;
            
        strcpy(dev1.bus, ptr);
        ptr = strtok(NULL,":");
        if(ptr == NULL)
            continue;
            
        strcpy(dev1.fun, ptr);
        ptr = strtok(NULL,"\n");
        if(ptr == NULL)
            continue;

        strcpy(dev1.name, ptr);
        dev1.ser_num+=1;
        fwrite(&dev1, sizeof(struct device), 1, db);
    }

    fclose(file);
    fclose(db);
#else
    db = fopen("/diag/bin/sup_lspci.db","r");
    if(db == NULL) {
        printf("Could not open file \n");
        return -1;
    } else
        printf("Reading from file\n");
    bzero(&dev1, sizeof(struct device));
    while(fread(&dev1, sizeof(struct device), 1, db) == 1) {
        dev_list_add_node(&head, &dev1);
    }
    fclose(db);
    
    bzero(&dev1, sizeof(struct device));
    /* Now do the comparisions */
    file = fopen("/tmp/lspci.txt","r");
    dev1.ser_num=0;
    while(!feof(file)) {
        fgets(str, 150, file);
        ptr = strtok(str,delim);
        if(ptr == NULL)
            continue;
        strcpy(dev1.bus, ptr);
        ptr = strtok(NULL,":");
        if(ptr == NULL)
            continue;
        strcpy(dev1.fun, ptr);
        ptr = strtok(NULL,"\n");
        if(ptr == NULL)
            continue;
        strcpy(dev1.name, ptr);
        dev1.ser_num+=1;
        dev_list_add_node(&nhead, &dev1);
    }

    fclose(file);
    dev_list_dump(head);
//   dev_list_dump(nhead);
    if(dev_list_comp(head, nhead) == 0)
        printf("PCIe scan test passed\n");
    else
        printf("PCIe scan test Failed\n");

    dev_list_free(&head);
    dev_list_free(&nhead);

#endif

}
