/*
 * This program to test BN_nmod() function
 */
#include <stdio.h>
#include <stdlib.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include "b283.h"
void init_ssl() {
	SSL_load_error_strings();
	SSL_library_init();
}

int main(int argc, char** argv) {
    BIGNUM *a = NULL, *b = NULL, *m = NULL, *mod_mul = NULL, *ret = NULL;
    BIGNUM *a_tmp = BN_new();
    char *order = "3ffffffffffffffffffffffffffffffffffef90399660fc938a90165b042a7cefadb307";
    char *inp = "77CB284AC41E72EDA2A93EB8D6DFF58620F6C69D528DFE90D909AA5CABC03A34E5D5A76";
    char *out;
    BN_hex2bn(&m, order);
    BN_hex2bn(&a, inp);
    int st = 0;
    BN_CTX *ctx;
    ctx = BN_CTX_new();
    BN_nnmod(a_tmp, a, m, ctx);
    out = BN_bn2hex(a_tmp); 
    printf("order:%s\n", order);
    printf("inp:%s\n", inp);
    printf("out:%s\n", out);
    OPENSSL_free(out);
    BN_free(a_tmp);
    BN_CTX_free(ctx);
}
