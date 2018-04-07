#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char **argv)
{
    int l=0,m=0;
    if(argc < 2) {
        printf("Need to pass at least one arg..\n");
        return 0;
    }
    printf("Args: %s\n", argv[1]);
    l = strlen(argv[1]) - 1;
    while(l>m){
        if(argv[1][l--] != argv[1][m++]){
            printf("Not polindrome\n");
            return 1;
        }
        printf("%c:%c \n ", argv[1][m], argv[1][l]);
    }
    printf("%s Is polindrome\n", argv[1]);
}
