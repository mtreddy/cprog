CC = gcc

#all: list lists queues stacks
all:  glists dlists queues stacks sets 

sets :	gen_sets.o lists.o
	$(CC) -o  get_sets gen_sets.o lists.o
gen_sets.o	:	gen_sets.c
	$(CC) -c -g3 gen_sets.c

stacks: gen_stacks.o lists.o
	$(CC) -o gen_stacks gen_stacks.o  lists.o
gen_stacks.o    :   gen_stacks.c
	$(CC)   -c  -g3 gen_stacks.c

queues : gen_queues.o lists.o
	$(CC) -o gen_queues gen_queues.o lists.o
gen_queues.o : gen_queues.c
	$(CC) -c -g3 gen_queues.c

glists : gen_llist.o lists.o
	$(CC) -o glists gen_llist.o lists.o

gen_llist.o : gen_llist.c gen_llist.h
	$(CC) -c -g3 gen_llist.c

dlists : double_llist.o
	$(CC) -o dlists double_llist.o

double_llist.o : double_llist.c
	$(CC) -c -g3 double_llist.c

lists.o :   lists.c gen_llist.h
	$(CC) -c -g3 lists.c

clean:
	rm gen_llist.o gen_queues.o gen_stacks.o lists.o gen_sets.o double_llist.o dlists
