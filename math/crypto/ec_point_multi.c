#include <stdio.h>
#include <stdlib.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/ssl.h>
void init_ssl() {
	SSL_load_error_strings();
	SSL_library_init();
}

struct test_x_y {
		const char *k, *x, *y;
};
static const struct test_x_y tp_x_y [] = {
		{
		/*k */
		"2",
	    /*x  */
	   "05F939258DB7DD90E1934F8C70B0DFEC2EED25B8557EAC9C80E2E198F8CDBECD86B12053",
	   /*	y */
		"05F939258DB7DD90E1934F8C70B0DFEC2EED25B8557EAC9C80E2E198F8CDBECD86B12053",
		},
};
int main() {
	EC_KEY   *eckey = NULL; /*"NID_sect283r1"*/
	const EC_GROUP *group = NULL;
	EC_POINT *pout = NULL;
	EC_POINT *tpout = NULL;
	BN_CTX *ctx;
   	BIGNUM *k = NULL, *x = NULL, *y = NULL;
	init_ssl();
	/*Get the ec curve*/
	eckey = EC_KEY_new_by_curve_name(NID_sect283r1);
	ctx = BN_CTX_new();
	BN_hex2bn(&x, tp_x_y[0].x); 
	BN_hex2bn(&y, tp_x_y[0].y); 
	BN_hex2bn(&k, tp_x_y[0].k); 
	group = EC_KEY_get0_group(eckey);
	pout = EC_POINT_new(group);
	tpout = EC_POINT_new(group);
	EC_POINT_mul(group, pout, k, NULL, NULL, ctx);
	char *cc = EC_POINT_point2hex(group, pout, 4, ctx);
	char *c = cc;
	int i;
	c++;
	c++;
     for (i=0; i<72; i++) // 1 byte 0x42, 32 bytes for X coordinate, 32 bytes for Y coordinate
     {
       printf("%c", *c++);
     }
    printf("\n");
     for (i=72; i<145; i++) // 1 byte 0x42, 32 bytes for X coordinate, 32 bytes for Y coordinate
     {
       printf("%c", *c++);
     }

    printf("\n");
    BN_CTX_free(ctx);
}
