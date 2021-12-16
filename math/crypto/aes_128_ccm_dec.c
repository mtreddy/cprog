#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

void str2hex(char *, char*, int);
void printBytes(unsigned char *, size_t );


int main(int argc, char **argv) {

    unsigned char *aad, *ict, *key, *nonce;
    int Klen, Alen, Nlen, Plen, Tlen, Clen;
    int outl = 0;

    key = "5a33980e71e7d67fd6cf171454dc96e5";
    aad = "eca622a37570df619e10ebb18bebadb2f2b49c4d2b2ff715873bb672e30fc0ff";
    nonce = "33ae68ebb8010c6b3da6b9cb29";
    ict = "a34dfa24847c365291ce1b54bcf8d9a75d861e5133cc3a74";
    Tlen = 16;
    if(argc > 1) {
	key =  argv[1];
	aad = argv[2];
	nonce = argv[3];
	ict = argv[4];
    	Tlen = atoi(argv[5]);
    	printf("key argv[1]=%s\n", argv[1]);
    	printf("aad argv[2]=%s\n", argv[2]);
    	printf("nonce argv[3]=%s\n", argv[3]);
    	printf("ctext argv[4]=%s\n", argv[4]);
    	printf("Tlen argv[5]=%s\n", argv[5]);
   } else {
	printf("if you want to pass custom plain text please pass as argument\n");
	printf(" ./ccm \"123456\" \n ");
	printf("Using default plain test\n");
   }

    Klen = strlen(key) / 2;
    Alen = strlen(aad) / 2;
    Nlen = strlen(nonce) / 2;
    Clen = strlen(ict) / 2;
    Plen = Clen - Tlen;

    unsigned char keyy[Klen], aadd[Alen], noncee[Nlen], ptt[Plen];
    unsigned char ct[Clen], dt[Plen];

    str2hex(key, keyy, Klen);
    str2hex(ict, ct, Clen);
    str2hex(aad, aadd, Alen);
    str2hex(nonce, noncee, Nlen);
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_CIPHER_CTX_init(ctx);

#if 0 
    EVP_EncryptInit(ctx, EVP_aes_128_ccm(), 0, 0);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_CCM_SET_IVLEN, Nlen, 0);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_CCM_SET_TAG, Tlen, 0);
    EVP_EncryptInit(ctx, 0, keyy, noncee);
    EVP_EncryptUpdate(ctx, 0, &outl, 0, Plen);
    EVP_EncryptUpdate(ctx, 0, &outl, aadd, Alen);
    EVP_EncryptUpdate(ctx, ct, &outl, ptt, Plen);
    EVP_EncryptFinal(ctx, &ct[outl], &outl);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_CCM_GET_TAG, Tlen, ct + Plen);
    printf("plaintext' = %s", pt);
    // printf("\nciphertext' = 7a60fa7ee8859e283cce378fb6b95522ab8b70efcdb0265f7c4b4fa597666b86dd1353e400f28864");
    printf("\n");

    printf("\nciphertext : ");
    printBytes(ct, Clen);
#endif

    EVP_DecryptInit(ctx, EVP_aes_128_ccm(), 0, 0);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_CCM_SET_IVLEN, Nlen, 0);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_CCM_SET_TAG, Tlen, ct + Plen);
    EVP_DecryptInit(ctx, 0, keyy, noncee);
    EVP_DecryptUpdate(ctx, 0, &outl, 0, Plen);
    EVP_DecryptUpdate(ctx, 0, &outl, aadd, Alen);
    EVP_DecryptUpdate(ctx, dt, &outl, ct, Plen);
    EVP_DecryptFinal(ctx, &dt[outl], &outl);
    printf("plaintext : ");
    printBytes(dt, Plen);
#if 0
    if(strncmp(pt, dt,strlen(pt)) == 0) 
	printf("\ntest pass\n");
    else
	printf("\ntest Failed\n");
#endif


    return 0;
}

void str2hex(char *str, char *hex, int len) {
    int tt, ss;
    unsigned char temp[4];
    for (tt = 0, ss = 0; tt < len, ss < 2 * len; tt++, ss += 2) {
        temp[0] = '0';
        temp[1] = 'x';
        temp[2] = str[ss];
        temp[3] = str[ss + 1];

        hex[tt] = (int) strtol(temp, NULL, 0);
    }
}

void printBytes(unsigned char *buf, size_t len) {
    int i;
    for (i = 0; i < len; i++) {
        printf("%02x", buf[i]);
    }
    printf("\n");
}
