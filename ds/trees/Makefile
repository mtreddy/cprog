CC = gcc

#all: list lists queues stacks
all: btree

btree:  ../lists/lists.o btree_build.o  btree_common.o
	$(CC) -o btree btree_build.o btree_common.o ../lists/lists.o

gen_llist.o : btree_build.c btree_common.c ../lists/lists.c btree_inc.h
	$(CC) -c -g3 btree_build.c btree_common.c  ../lists/lists.c

clean:
	rm build_btree.o btree_common.o 
