/*
 *  gcc -o aes_ccm aes_ccm.c -lssl -lcrypto
 *  Encrypt test:
 *  ./aes_ccm  "enc256"  "d62a4127c75d83db5363a4a4655e4157adb92c207b2c565a8a093a3b201959d8" "af1d62deec2491f957f5400b6eec7fda" "979b2febf2c854f4"   ptext.txt
 *  Decrypt test
 *  ./aes_ccm  "dec256"  "d62a4127c75d83db5363a4a4655e4157adb92c207b2c565a8a093a3b201959d8" "af1d62deec2491f957f5400b6eec7fda" "979b2febf2c854f4" ctext.txt
 */
#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
/*
 *  How to generate AES 128bit or 256 bit key : openssl rand -hex 16 or openssl rand -hex 32 
 *  How to convert plain text from bin to hex: you can use xdd
 */
void str2hex(char *, char*, int);
void printBytes(unsigned char *, size_t );
#define MAXLINE 1024
typedef unsigned char uchar;
void aes_ccm_encrypt( char *optype, int Klen, int Alen,int  Nlen,int  Plen,int  Tlen,int  Clen,
		uchar keyy[], uchar aadd[], uchar noncee[], uchar ptt[], uchar ct[], uchar pt[]);
void aes_ccm_decrypt( char *optype, int Klen, int Alen,int  Nlen,int  Plen,int  Tlen,int  Clen,
		uchar keyy[], uchar aadd[], uchar noncee[], uchar dt[], uchar ct[]);
int main(int argc, char **argv) {
    //unsigned char *aad, pt[MAXLINE], *key, *nonce;
    int Klen, Alen, Nlen, Plen, Tlen, Clen;
    int outl = 0;

    uchar *key = "d62a4127c75d83db5363a4a4655e4157adb92c207b2c565a8a093a3b201959d8";
    uchar *aad = "af1d62deec2491f957f5400b6eec7fda";
    uchar *nonce = "979b2febf2c854f4";
    uchar pt[MAXLINE];
    Tlen = 16;
    if(argc >  1) {
	printf("aes_ccm <op-type> <key> <aad> <nonce> <plain text file>\n");
        key =  argv[2];
        aad = argv[3];
        nonce = argv[4];
        //Tlen = atoi(argv[5]);
        //printf("Tlen=%d\n", Tlen);
	FILE *fp = fopen(argv[5], "r");
	if(!fp) {
		printf("Failed to open plain text\n");
		return -1;
	}
	printf("File opend\n");
	if(fgets(pt, MAXLINE, fp) == 0) {
		printf("No plain text input\n");
	}
	printf("op:%s\n", argv[1]);
	printf("key:%s\n", argv[2]);
	printf("aad=%s\n",argv[3]);
	printf("nonce=%s\n", argv[4]);
	printf("Tex file =%s\n", argv[5]);
        printf("plain-text=%s\n", pt);
    } else {
 	  printf("Default test is aes128 CCM encrypt\n");
    }
    Klen = strlen(key) / 2;
    Alen = strlen(aad) / 2;
    Nlen = strlen(nonce) / 2;

    unsigned char keyy[Klen], aadd[Alen], noncee[Nlen];
    str2hex(key, keyy, Klen);
    str2hex(aad, aadd, Alen);
    str2hex(nonce, noncee, Nlen);
    if((strcmp(argv[1], "enc128") == 0) || (strcmp(argv[1], "enc192") == 0) || (strcmp(argv[1], "enc256") == 0)){
	/*Validate params*/
	printf("AES CCM Encrypt\n");
    	Plen = strlen(pt) / 2;
    	Clen = Plen + Tlen;
    	unsigned char ct[Clen], ptt[Plen];
    	printf("klen-%d Alen-%d Nlen-%d Plen-%d Clen=%d\n", Klen, Alen, Nlen, Plen, Clen);
        str2hex(pt, ptt, Plen);
	aes_ccm_encrypt(argv[1], Klen, Alen,Nlen,Plen,Tlen,Clen, keyy, aadd, noncee, ptt, ct, pt);
    } else if((strcmp(argv[1], "dec128") == 0) || (strcmp(argv[1], "dec192") == 0) || (strcmp(argv[1], "dec256") == 0)){
   	printf("AES CCM Decrypt\n");
    	Clen = strlen(pt) / 2;
    	Plen = Clen - Tlen;
    	unsigned char ct[Clen], dt[Plen];
    	printf("klen-%d Alen-%d Nlen-%d Plen-%d Clen=%d\n", Klen, Alen, Nlen, Plen, Clen);
        str2hex(pt, ct, Clen);
	aes_ccm_decrypt( argv[1], Klen, Alen, Nlen, Plen, Tlen, Clen, keyy, aadd, noncee,  dt, ct);
    } else {
       printf("Invalid selectiob\n");
    }

}

void aes_ccm_encrypt( char *optype, int Klen, int Alen,int  Nlen,int  Plen,int  Tlen,int  Clen,
		uchar keyy[], uchar aadd[], uchar noncee[], uchar ptt[], uchar ct[], uchar pt[]){
    	int outl = 0;
	EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    	EVP_CIPHER_CTX_init(ctx);
	if(strcmp(optype, "enc192") == 0) 
    	   EVP_EncryptInit(ctx, EVP_aes_192_ccm(), 0, 0);
	else if(strcmp(optype, "enc256") == 0) 
    	   EVP_EncryptInit(ctx, EVP_aes_256_ccm(), 0, 0);
	else 
    	   EVP_EncryptInit(ctx, EVP_aes_128_ccm(), 0, 0);

     	EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_CCM_SET_IVLEN, Nlen, 0);
    	EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_CCM_SET_TAG, Tlen, 0);
    	/* Set key and IV or Nonce*/
    	EVP_EncryptInit(ctx, 0, keyy, noncee);
    	/* Set plain text length */
    	EVP_EncryptUpdate(ctx, 0, &outl, 0, Plen);
    	/* Call to specify aad*/
    	EVP_EncryptUpdate(ctx, 0, &outl, aadd, Alen);
    	/* Encrypt plain text*/
    	EVP_EncryptUpdate(ctx, ct, &outl, ptt, Plen);
    	/*Finalize: note get no output for CCM*/
    	EVP_EncryptFinal(ctx, &ct[outl], &outl);
    	/* Get TAG */
    	EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_CCM_GET_TAG, Tlen, ct + Plen);

    	printf("plaintext' = %s", pt);
    	// printf("\nciphertext' = 7a60fa7ee8859e283cce378fb6b95522ab8b70efcdb0265f7c4b4fa597666b86dd1353e400f28864");
    	printf("\n");

    	printf("\nciphertext : ");
    	printBytes(ct, Clen);
}
void aes_ccm_decrypt( char *optype, int Klen, int Alen,int  Nlen,int  Plen,int  Tlen,int  Clen,
		uchar keyy[], uchar aadd[], uchar noncee[],  uchar dt[], uchar ct[]){
    	int outl = 0;
	EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
	if(strcmp(optype, "dec192") == 0) 
	   EVP_DecryptInit(ctx, EVP_aes_192_ccm(), 0, 0);
	if(strcmp(optype, "dec256") == 0) 
	   EVP_DecryptInit(ctx, EVP_aes_256_ccm(), 0, 0);
	else
	   EVP_DecryptInit(ctx, EVP_aes_128_ccm(), 0, 0);
	EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_CCM_SET_IVLEN, Nlen, 0);
	EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_CCM_SET_TAG, Tlen, ct + Plen);
	EVP_DecryptInit(ctx, 0, keyy, noncee);
	EVP_DecryptUpdate(ctx, 0, &outl, 0, Plen);
	EVP_DecryptUpdate(ctx, 0, &outl, aadd, Alen);
	EVP_DecryptUpdate(ctx, dt, &outl, ct, Plen);
	EVP_DecryptFinal(ctx, &dt[outl], &outl);
	printf("plaintext : ");
#if 0
	if(strncmp(pt, dt,strlen(pt)) == 0)
	   printf("\ntest pass\n");
	else
	   printf("\ntest Failed\n");
#else
	printBytes(dt, Plen);
#endif
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

