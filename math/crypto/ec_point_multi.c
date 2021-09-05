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
# if 0
struct test_x_y {
		const char *k, *x, *y;
};
static const struct test_x_y tp_x_y [] = {
		{
		/*k */
		"1",
	    /*x  */
		"05F939258DB7DD90E1934F8C70B0DFEC2EED25B8557EAC9C80E2E198F8CDBECD86B12053",
	   /*	y */
		"03676854FE24141CB98FE6D4B20D02B4516FF702350EDDB0826779C813F0DF45BE8112F4",
		},
};
#endif
int main() {
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
			printf("Doesnt Matche %d\n", val);
#if 1		
			char *cc = EC_POINT_point2hex(group, pout, 4, ctx);
			char *c = cc;
			int i;
			c++;
			c++;
			for (i=0; i<72; i++) // 1 byte 0x42, 32 bytes for X coordinate, 32 bytes for Y coordinate
		       	   printf("%c", *c++);
		    	printf("\n");
		        for (i=72; i<145; i++) // 1 byte 0x42, 32 bytes for X coordinate, 32 bytes for Y coordinate
		       	   printf("%c", *c++);
		    	printf("\n");
#endif
		}
	}
    BN_CTX_free(ctx);
}
