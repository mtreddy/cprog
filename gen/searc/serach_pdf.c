/*
 * There is no direct search possible in C. You need to get relavant libraries.
 * pdf2txt.py is program  which can convert pdf to txt.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

 char str[] = "/usr/local/bin/pdf2txt.py -o ./nlp.txt ~/Documents/ml/nlp/NaturalLanguageProcessingWithPython.pdf";

 int main(int argc, char  **argv)
{
    FILE *fp = NULL;
    char pattrn[50];
    char *ptr = NULL;
    int rc = 0;
    if(argc < 2)  {
        printf("syntax: ./pdf_search <string to search>\n");
        return 0;
    }
    /*We only support pattern size 50*/
    if(strlen(argv[1]) >= 50) {
        printf("Too long please pass pattern size less then 50 chars\n");
        return -1; 
    }
    if(strcpy(pattrn, argv[1]) == 0) {
        printf("No pattern to search...\n");
    }
    /*Run command line command*/
     rc = system("str");
     if(rc != 0) {
         printf("Failed to conver to txt WEXITSTATUS(%d) = %d \n", rc, WEXITSTATUS(rc));
         return  -1;
     }
    
    fp = fopen("./nlp.txt", "r");
    if( fp == NULL) {
        printf("Failed to open file nlp.txt\n");
        return -1;
    }
    while(!feof(fp)) { 
        fgets(str, 100, fp); 
        ptr = strstr(str, pattrn); 
        if(ptr != NULL) {
            printf(" Found string in the file...!\n");
            goto _finish;
        }
    }
    printf("Pattern %s not found\n", pattrn);
_finish:
    if(fp) fclose(fp);
}

