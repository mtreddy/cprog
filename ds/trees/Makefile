CC = gcc
CPP = g++

#all: list lists queues stacks
all: btree btview

btview: btree_top_view.o
	$(CPP) -o btview btree_top_view.o

btree_top_view.o: btree_top_view.cpp
	$(CPP) -c -g3 btree_top_view.cpp

btree:  ../lists/lists.o btree_build.o  btree_common.o
	$(CC) -o btree btree_build.o btree_common.o ../lists/lists.o

gen_llist.o : btree_build.c btree_common.c ../lists/lists.c btree_inc.h
	$(CC) -c -g3 btree_build.c btree_common.c  ../lists/lists.c

clean:
	rm build_btree.o btree_common.o 
