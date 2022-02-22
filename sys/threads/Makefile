## Makefie


CC = gcc
CFLAGS = -g3
LDFLAGS = -lpthread
all:  thread1
bin = thread1
input: thread1.c 

$(all): 
	$(CC) ${CFLAGS}  -c $< -o $@ ${LDFLAGS}

clean:
	rm ${bin}

