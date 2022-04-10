#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Insert numer and name into hash.
 * Algorithm to use is modulus (num %100) if there is number greater than 1000 then they will be added to the list
 * Example list
 *   1 ->[1]["linda"]->[1001]["loarry"]
 *   2->
 *   3->
 *   4->[4]["summers"]
 */
#define MAX_ELEMENTS 100

struct clist{
        int num;
        char name[50];
        struct clist *next;
};

/* Array of struct pointers*/
struct clist *list[MAX_ELEMENTS];

void insert(struct clist **node){
        if(*node != NULL) {
                if(list[(*node)->num%MAX_ELEMENTS] == NULL) {
                        list[(*node)->num%MAX_ELEMENTS] = *node;
                        return;
                } else {
                    struct clist *tmp = list[(*node)->num%MAX_ELEMENTS];
                    while(tmp->next != NULL) {
                        tmp = tmp->next;
                    }
                    tmp->next = *node;
                }
        }
}

struct clist *find(int num){
        struct clist *tmp = list[num%MAX_ELEMENTS];
        if(tmp->num == num)
                return tmp;
        else {
                while(tmp->next != NULL) {
                        if(tmp->num == num)
                                return tmp;
                        tmp = tmp->next;
                }
        }
        return tmp;
}
void print(struct clist *pr){
        printf("Numer=%d  Name=%s\n", pr->num, pr->name);
}
void init(void){
    int ind = 0;
    while(ind < MAX_ELEMENTS){
        list[ind] = NULL;
        ind++;
    }
}
int main(void){
        struct clist *tst = NULL;
        init();
        tst = (struct clist *)malloc(sizeof(struct clist));
        tst->num = 40;
        strcpy(tst->name, "Vallerie");
        insert(&tst);
        tst = (struct clist *)malloc(sizeof(struct clist));
        tst->num = 50;
        strcpy(tst->name, "victor");
        insert(&tst);

        tst = find(50);
        print(tst);
        return 0;

}
