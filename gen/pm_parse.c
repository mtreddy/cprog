include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct  pm_data {
    int offset;
    int val;
    struct pm_data *next;
};

void pm_add_node(struct pm_data **head, int offset, int val)
{
    struct pm_data *tmp = *head;

    if(tmp == NULL) {
        tmp = (struct pm_data *)malloc(sizeof(struct pm_data));
        tmp->offset = offset;
        tmp->val = val;
        tmp->next = NULL;
        *head = tmp;
        return;
    }
    
    while(tmp->next != NULL) {
        tmp=tmp->next;
    }

    tmp->next = (struct pm_data *)malloc(sizeof(struct pm_data));
    tmp->next->offset = offset;
    tmp->next->val = val;
    tmp->next->next = NULL;
    return;
}

void pm_dump(struct pm_data *head)
{
    struct pm_data *tmp = head;

    while(tmp != NULL) {
        printf("offset 0x%x val 0x%x\n", tmp->offset, tmp->val);
        tmp = tmp->next;
    }
}

int main(int argc, char **argv)
{
    struct pm_data *head = NULL;
    char str[100];
    char str1[100];
    char buf[50];
    char *ptr;
    char delim[] = ",";
    int offset = 0;
    int val = 0;
    ILE *file = NULL;
    if(argc < 2)
        printf("Usage: pm_parse ./file_name.csv");

    file = fopen(argv[1], "r");
    if(file == NULL) {
        printf("Failed to open file %s \n", argv[1]);
        return -1;
    }

    while(!feof(file)) {
        fgets(str,100, file);
        ptr = strstr(str, "WriteByte");
        if(ptr != NULL) {
            /*Alloc node*/
            strcpy(str1,str);
            ptr = strtok(str, delim);
            if(ptr != NULL)
                printf("ptr = %s\n", ptr);
            else
                continue;
            ptr = strtok(NULL, delim);
            if(ptr != NULL)
                printf("ptr = %s\n", ptr);
            else
                continue;
            offset = strtoul(ptr, NULL, 0);
            ptr = strtok(NULL, delim);
            if(ptr != NULL)
                printf("ptr = %s\n", ptr);
            else
                continue;
            val = strtoul(ptr, NULL, 0);
            pm_add_node(&head, offset, val);
        }

    }

    pm_dump(head);
    
    return 0;

}

