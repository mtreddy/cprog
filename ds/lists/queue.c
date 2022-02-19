#include<stdio.h>
#include<malloc.h>

struct node {
	int val;
	struct node *next;
};

struct queue{
	struct node *head;
};
struct queue que;
void qpush(int val){
	if(que.head == NULL) {
		que.head = (struct node *)malloc(sizeof(struct node));
		que.head->val = val;
		que.head->next = NULL;
		return;
	}
	struct node *tmp = NULL;
	tmp = (struct node *)malloc(sizeof(struct node));
	tmp->val = val;
	tmp->next = que.head;
	que.head = tmp;
	return;
}
int  qpop(void){
	struct node *tmp;
	struct node *prev;
	int val = 0;
	tmp = que.head;
	if(tmp == NULL)
		return -1;
	/*Reach end of the queu */
	prev = tmp;
	while(tmp->next != NULL) {
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = NULL;
	val = tmp->val;
	free(tmp);
	return val;
	
}
void print_queue(void){
	struct node *tmp = que.head;
	while(tmp) {
		printf(" %d \n", tmp->val);
		tmp = tmp->next;
	}
}
int main()
{
 	qpush(10);
 	qpush(100);
 	qpush(101);
 	qpush(99);
	print_queue();
	printf("pop val %d\n", qpop());
	printf("pop val %d\n", qpop());
	printf("pop val %d\n", qpop());

    return 0;
}
