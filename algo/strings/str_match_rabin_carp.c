#include<stdio.h>
#include<string.h>

#define d 256

int search(char pat[], char txt[], int q)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int h = 1;
    int i = 0, j = 0;
    int p = 0;
    int t = 0;

    /* The value of h would be "pow(d, M-1)%q"*/
    for(i=0;i<M-1;i++)
        h = (h*d)%q;
    /*Calculate the hash value for txt and pattern*/
    for(i=0;i<M;i++) {
        p = (d*p + pat[i])%q;
        t = (d*t + txt[i])%q;
    }
    printf("M=%d N = %d\n", M, N);
    printf("p=%d t = %d\n", p, t);
    printf("h=%d \n", h);

    /*now check in txt*/
    for(i=0;i<N-M;i++){
        if(p == t) {
            for(j=0;j<M;j++){
                if(txt[i+j] != pat[j])
                    break;
            }
            if(j == M)
                printf("Pattern %s found\n", pat);
        }
        if(i < N-M) {
            t = (d*(t - txt[i]*h) + txt[i+M])%q;
            if(t<0) 
                t = (t + q);
        }
    printf("p=%d t = %d\n", p, t);
    }
    return 0;
}

int main(int argc, char **argv)
{
    char str1[25], str2[25];
    int i = 0, j = 0;
    int q = 101;
    if(argc < 3) {
        printf("Exampl: ./str_match str1 str2");
    }
    if(strlen(argv[1]) >= 25) {
        printf("Source arg is toolong\n");
        return 1;
    }
    if(strlen(argv[2]) >= 25) {
        printf("Target arg is toolong\n");
        return 1;
    }
    if(strlen(argv[1]) < strlen(argv[2])) {
        printf("Source is shorter than target\n");
        return 1;
    }
    strcpy(str1, argv[1]);
    strcpy(str2, argv[2]);
    printf("Searching for %s in %s\n", str2, str1);
    search(str2, str1, q);
}
