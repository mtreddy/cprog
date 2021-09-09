/*
 * Example usage
 *  ./ec_point_multi  "1" "05F939258DB7DD90E1934F8C70B0DFEC2EED25B8557EAC9C80E2E198F8CDBECD86B12053" "03676854FE24141CB98FE6D4B20D02B4516FF702350EDDB0826779C813F0DF45BE8112F4"
 *  if there is a miss match program will print the calculated point on the curve.
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
void print_ec_point(const EC_GROUP *group, EC_POINT *pout, BN_CTX *ctx) {
	char *cc = EC_POINT_point2hex(group, pout, 4, ctx);
	char *c = cc;
	int i;
	c++;
	c++;
	printf("x: ");
	for (i=0; i<72; i++) // 1 byte 0x42, 32 bytes for X coordinate, 32 bytes for Y coordinate
       	   printf("%c", *c++);
    	printf("\n");
	printf("y: ");
        for (i=72; i<145; i++) // 1 byte 0x42, 32 bytes for X coordinate, 32 bytes for Y coordinate
       	   printf("%c", *c++);
    	printf("\n");
}
int main(int argc, char** argv) {
	EC_KEY   *eckey = NULL; /*"NID_sect283r1"*/
	const EC_GROUP *group = NULL;
	EC_POINT *pout = NULL;
	EC_POINT *Q_CHECK = NULL;
	BN_CTX *ctx;
   	BIGNUM *k = NULL, *x = NULL, *y = NULL;
	int i = 0;
	init_ssl();
	/*Get the ec curve*/
	eckey = EC_KEY_new_by_curve_name(NID_sect283r1);
	group = EC_KEY_get0_group(eckey);
	pout = EC_POINT_new(group);
	Q_CHECK = EC_POINT_new(group);
	ctx = BN_CTX_new();
	if(argc == 4) { 
		struct test_x_y *tpp_x_y;
		tpp_x_y->k = argv[1];
		tpp_x_y->x = argv[2];
		tpp_x_y->y = argv[3];
		BN_hex2bn(&x, tpp_x_y->x); 
		BN_hex2bn(&y, tpp_x_y->y); 
		BN_dec2bn(&k, tpp_x_y->k); 
		EC_POINT_mul(group, pout, k, NULL, NULL, ctx);
		EC_POINT_set_affine_coordinates(group, Q_CHECK, x, y, ctx);
		int val = EC_POINT_cmp(group, pout, Q_CHECK, ctx);
		printf("k:%s\n", tp_x_y->k);
		if (val == 0) 
			printf("Matches\n");
		else {
			printf("Doesnt Match input x & y. Expected x & y are  as below \n");
			print_ec_point(group, pout, ctx);
		}
	}else{
	for(i = 0; i < sizeof(tp_x_y)/sizeof(tp_x_y[0]); i++) {
		BN_hex2bn(&x, tp_x_y[i].x); 
		BN_hex2bn(&y, tp_x_y[i].y); 
		BN_dec2bn(&k, tp_x_y[i].k); 
		EC_POINT_mul(group, pout, k, NULL, NULL, ctx);
		EC_POINT_set_affine_coordinates(group, Q_CHECK, x, y, ctx);
		int val = EC_POINT_cmp(group, pout, Q_CHECK, ctx);
		printf("k:%s\n", tp_x_y[i].k);
		if (val == 0) 
			printf("Matches\n");
		else {
			printf("Doesnt Match Expected x & y as below \n");
			print_ec_point(group, pout, ctx);
		}
	}
	}
    BN_CTX_free(ctx);
}
