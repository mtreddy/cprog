#include<stdio.h>
#include<string.h>

int main(int argc, char **argv)
{
    char str1[25], str2[25];
    int i = 0, j = 0;
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

    while(str1[i] != '\0') {
        while(str2[j] != '\0') {
            if(str1[i + j] == str2[j]) {
                j++;
            } else
                break;
        }
        if(str2[j] == '\0') {
            printf("Match found for %s in %s\n", str2, str1);
        }
        i++;
        j = 0;
    }
}
