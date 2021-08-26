
CC = gcc

CFLAGS = -g3


all:   array cmalloc1 cmalloc funcptr funcptr1 funcptr2 funcptr3 malloc1 malloc mallocm


array: array.c
	$(CC) $(CFLGAGS) -o array array.c
      
cmalloc1:      cust_malloc_1.c  
	$(CC) $(CFLGAGS)  -o cmalloc1 cust_malloc_1.c
cmalloc: cust_malloc.c  
	$(CC) $(CFLGAGS)  -o cmalloc cust_malloc.c
funcptr: func_ptr.c  
	$(CC) $(CFLGAGS) -o funcptr func_ptr.c
funcptr1: func_ptr_1.c  
	$(CC) $(CFLGAGS) -o funcptr1 func_ptr_1.c
funcptr2: func_ptr_2.c  
	$(CC) $(CFLGAGS)  -o funcptr2 func_ptr_2.c
funcptr3:  func_ptr_3.c  
	$(CC) $(CFLGAGS) -o funcptr3 func_ptr_3.c 
malloc1:	malloc_1.c  
	$(CC) $(CFLGAGS) -o malloc1 malloc_1.c
malloc: malloc.c  
	$(CC) $(CFLGAGS) -o malloc malloc.c

mallocm: malloc_m.c
	$(CC) $(CFLGAGS) -o mallocm malloc_m.c

clean:
	rm array cmalloc1 cmalloc funcptr funcptr1 funcptr2 funcptr3 malloc1 malloc mallocm
