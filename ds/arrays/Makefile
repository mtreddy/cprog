CC = gcc

#all: list lists queues stacks
all: rotate

rotate:  ../lists/lists.o rotate.o  array_common.o
	$(CC) -o rotate rotate.o array_common.o 

gen_llist.o : rotate.c array_common.c array_inc.h
	$(CC) -c -g3 rotate.c array_common.c  

clean:
	rm rotate.o array_common.o 
