#export LD_LIBRARY_PATH="/User_data/home/tmarri/src/crypto/openssl/openssl-1.1.1k/"
#openssl="/User_data/home/tmarri/src/crypto/openssl/openssl-1.1.1k/apps/openssl"
CPP = g++
CC = gcc
LD = ld
export LD_LIBRARY_PATH=/User_data/home/tmarri/src/crypto/openssl/openssl-1.1.1k/
all: large_num_ops ec_point_mul

CFLAGS = 
LD_FLAGS = -L/User_data/home/tmarri/src/crypto/openssl/openssl-1.1.1k/
LDLIBS= -lssl -lcrypto

large_num_ops: large_num_ops.cpp
	$(CPP) -o large_num_ops large_num_ops.cpp

ec_point_mul: ec_point_multi.c
	$(CC) ec_point_multi.c -o ec_point_mul $(LD_FLAGS) $(LDLIBS)

clean:
	rm large_num_ops ec_point_mul
