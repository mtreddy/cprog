#export LD_LIBRARY_PATH="/User_data/home/tmarri/src/crypto/openssl/openssl-1.1.1k/"
#openssl="/User_data/home/tmarri/src/crypto/openssl/openssl-1.1.1k/apps/openssl"
CPP = g++
CC = gcc
LD = ld
export LD_LIBRARY_PATH=/User_data/home/tmarri/src/crypto/openssl/openssl-1.1.1k/
all: large_num_ops ec_point_multi bn_nnmod_test openssl_ec_keygen ssl_client ssl_server 

CFLAGS = -g3
LD_FLAGS = -L/User_data/home/tmarri/src/crypto/openssl/openssl-1.1.1k/
LDLIBS= -lssl -lcrypto

large_num_ops: large_num_ops.cpp
	$(CPP) -o large_num_ops large_num_ops.cpp

ec_point_multi: ec_point_multi.c
	$(CC)  $(CFLAGS) ec_point_multi.c -o ec_point_multi $(LD_FLAGS) $(LDLIBS)

bn_nnmod_test: bn_nnmod_test.c
	$(CC)  $(CFLAGS) bn_nnmod_test.c -o bn_nnmod_test $(LD_FLAGS) $(LDLIBS)

openssl_ec_keygen: openssl_ec_keygen.c
	$(CC)  $(CFLAGS) openssl_ec_keygen.c -o openssl_ec_keygen $(LD_FLAGS) $(LDLIBS)

ssl_client:
	$(CC)  $(CFLAGS) ssl_client.c -o ssl_client $(LD_FLAGS) $(LDLIBS)

ssl_server:
	$(CC)  $(CFLAGS) ssl_server.c -o ssl_server $(LD_FLAGS) $(LDLIBS)

clean:
	rm large_num_ops ec_point_multi bn_nnmod_test ssl_client ssl_server
