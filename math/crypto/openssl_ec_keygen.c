#include <openssl/opensslconf.h>
#include <stdio.h>
#include "apps.h"
#include "progs.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/bn.h>
#include <openssl/ec.h>
#include <openssl/x509.h>
#include <openssl/pem.h>


/*
 *  Args cruve="secp192r1"
 */
int main(int argc, char **argv) {
	char *group;
	int nid = 0; /*Cureve ids*/
    	BIO *in = NULL, *out = NULL;
    	char *infile = NULL, *outfile = NULL, *prog;
        int asn1_flag = OPENSSL_EC_NAMED_CURVE, new_asn1_flag = 0;
        int informat = FORMAT_PEM, outformat = FORMAT_PEM, noout = 0, C = 0;
        EC_KEY *eckey = EC_KEY_new();
        if (eckey == NULL)
		goto end;
	if(strcmp(argv[1], "secp192r1") == 0)  {
		nid = NID_X9_62_prime192v1;
	} else  if(strcmp(argv[1], "secp256r1") == 0)  {
		nid = NID_X9_62_prime256v1;
	} else {
		nid = OBJ_sn2nid(curve_name);
	}

	/*Set up group*/
	group = EC_GROUP_new_by_curve_name(nid);
	if (group == NULL) {
		BIO_printf(bio_err, "unable to create curve (%s)\n", argv[1]);
		goto out;
	}
        if (!EC_KEY_generate_key(eckey)) {
		BIO_printf(bios_err, "Unable to generate key\n");
		EC_KEY_free(eckey);
		goto end;
	}
        ECPKParameters_print(out, group, 0);
        if (outformat == FORMAT_ASN1)
            i = i2d_ECPrivateKey_bio(out, eckey);
        else
            i = PEM_write_bio_ECPrivateKey(out, eckey, NULL,
                                           NULL, 0, NULL, NULL);
	
end:
	BN_free();
}
