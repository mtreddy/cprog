CC = gcc
LIBS = -L/usr/lib 
#all: list lists queues stacks
all: ssl_client ssl_server 

ssl_client :	 ssl_client.o
	$(CC) -o  ssl_client ssl_client.o -lssl -lcrypto $(LIBS)
ssl_client.o	:	ssl_client.c
	$(CC) -c -g3 ssl_client.c

ssl_server:	 ssl_server.o
	$(CC) -o  ssl_server ssl_server.o  -lssl -lcrypto $(LIBS)
ssl_server.o	:	ssl_server.c
	$(CC) -c -g3 ssl_server.c


clean:
	rm ssl_cleint ssl_server 
