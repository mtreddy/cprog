#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define PARAM_LENGTH 32
#define MAX_PARAMS 8
void parse_args(char *iargs, char **oargs, int *nargs){
        printf("Parsing args\n");
        if(iargs == NULL) {
                printf("Input args is NULL\n");
                return ;
        }
        int ind = 0;
        char *ch = NULL;
        ch = strtok(iargs, " ");
        while(ch!= NULL) {
                strncpy(oargs[ind], ch, strlen(ch));
                /*Add end of str charecter*/
                oargs[ind][strlen(ch)] = '\0';
                /*Convert to lower case*/
                for(int lind=0; lind < strlen(oargs[ind]); lind++)
                        { oargs[ind][lind] = tolower(oargs[ind][lind]);}
                printf("%s\n", ch);
                ind++;
                ch = strtok(NULL, " ");
        }
        printf("Number of tokens.. %d\n", ind);
        *nargs = ind;
}
int run(int nargs, char** args) {
        for(int ind = 0; ind < nargs; ind++) {
                printf("run %s\n", args[ind]);
                if(strncmp(args[ind], "exit", sizeof("exit")-1) == 0) {
                        return 1;
                }
        }
        return 0;
}
int main(int argc, char **argv) {

        char arguments[MAX_PARAMS][PARAM_LENGTH];
        char *shell_argv[MAX_PARAMS];
        if (argc >1 ) {
                printf("More args\n");
        } else {
                for (int i = 0; i<MAX_PARAMS; i++) {
                        shell_argv[i] = arguments[i];
                }
                strncpy(shell_argv[0], argv[0], PARAM_LENGTH);
        }
        size_t size_alloc = 0;
        char *buff = NULL;
        int pargs;


        do {
                printf("[HSM] ");
                size_t input = getline(&buff, &size_alloc, stdin);
                printf(" %s\n", buff);
                printf("%lu\n", input);
                parse_args(buff, &shell_argv[0], &pargs);
                int ret = run(pargs, &shell_argv[0]);
                if(ret == 1) {
                        printf("Exiting CLI..\n");
                        break;
                }
        }while(1);
}
