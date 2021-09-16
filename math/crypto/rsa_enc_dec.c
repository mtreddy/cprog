#include <stdio.h>
#include <stdlib.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/ssl.h>

/*
 * char *n = "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5";
  char *e = "010001";
   char *d = "74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D";
*/

BIGNUM *encrypt(BN_CTX *ctx, BIGNUM *M, BIGNUM *e, BIGNUM *n){
   BIGNUM *C = BN_new();
   BN_mod_exp(C,M,e,n,ctx);
   return C;
}


BIGNUM *decrypt(BN_CTX *ctx, BIGNUM *C, BIGNUM *d, BIGNUM *n){
   BIGNUM *M = BN_new();
   BN_mod_exp(M,C,d,n,ctx);
   return M;
}

int main () {
	char *c = NULL;
	char *m = NULL;
	BIGNUM *C = BN_new();
	BIGNUM *M = BN_new();
	BN_hex2bn(&n, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");
	BN_hex2bn(&e, "010001");
	BN_hex2bn(&d, "74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");
	C=encrypt(ctx,M,e,n);
	BN_bn2hex(&c, C);
	printf("Encryped Message:%s\n", c);
	M=decrypt(ctx,C,d,n);
	BN_bn2hex(&m, M);
	printf("Decrypted Message:%s\n", c);
  
}

