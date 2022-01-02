//gcc -I~/src/crypto/openssl/openssl-1.1.1k/  -L~/src/crypto/openssl/openssl-1.1.1k/  -o x_y_to_pem  x_y_to_pem.c -lssl -lcrypto -g3
/*
 * THis is example code showing how to convert ECC public key   x,y coardinates on ECC curver into public key PEM format
 *  ## To dump the pem file just created: openssl ec -pubin -in  283pub.pem  -text
 */
#include <stdio.h>
#include <openssl/ec.h>
#include <openssl/pem.h>
#include <openssl/bio.h>

 //  int nid = NID_secp256k1;
//const char *xHex = "053b5b02d673e6f115b538de3587318821149d3e7bc65903f300b8cfffcacdaa";
//const char *yHex = "75e5d460e9d407672ff86683b748b6e882b361fa2fdf78845f8a9a369f6d016e";
  // int nid = NID_secp384r1;
//const char *xHex = "871d78c09728235d47696e2e118524e5645d65db82d1982b5c95f1e9fd195dfeca61d3963b34157bd5a70fcee9964961";
//const char *yHex = "866cd48e3779c3613e250b16d2ee571761022b6439bcdc47808f601e8038ea6602fda82baab179b463068bb5b84a87b4";
int main(
    int argc,
    char **argv)
{
    EC_KEY *eckey = NULL;
    EC_GROUP *group;
    EC_POINT *pout = NULL;
    BIGNUM *x = NULL, *y = NULL;
    BIO *fp = NULL;
    int nid = 0;
    if (argc ==  5) {
	printf("Passed variables:\n");
	printf("curve-id 	:%s\n", argv[1]);
	printf(" yarg		:%s\n", argv[2]);
	printf(" yarg		:%s\n", argv[3]);
	printf(" pem filename 	:%s\n", argv[4]);
        nid = atoi(argv[1]);
	BN_hex2bn(&x, argv[2]);
	BN_hex2bn(&y, argv[3]);
        fp = BIO_new_file(argv[4], "w");
	printf("curve-id %d\n", nid);
    } else {
	printf("Using default params for sect283r1\n");
	const char *xHex = "0794ce8d5d9387dbb46b5e83b0fe67b03134e56ea2ebfd2dd05d4f918580a30a58c7df5a";
	const char *yHex ="03f08daa6fe2b43eda785951348e9fede1acfc972762d50376ef6dda9ca3faad792f53ff";
        nid = NID_sect283r1;
        fp = BIO_new_file("ptest.pem", "w");
   	BN_hex2bn(&x, xHex);
	BN_hex2bn(&y, yHex);
    }
    eckey = EC_KEY_new_by_curve_name(nid);

    EC_KEY_set_public_key_affine_coordinates(eckey, x, y);
    EC_KEY_set_asn1_flag(eckey, OPENSSL_EC_NAMED_CURVE);
    //PEM_write_EC_PUBKEY(fp, eckey);
    PEM_write_bio_EC_PUBKEY(fp, eckey);
    BN_free(x);
    BN_free(y);
    EC_KEY_free(eckey);
}
