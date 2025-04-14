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
struct cmd{
        const char *name;
        int(*f)(int argc, char** argv);

};
int help(int argc, char** argv) {
        printf("help called\n");
        return 0;
}
int app_init(int argc, char** argv) {
        printf("Init called\n");
        return 0;
}
int app_login(int argc, char** argv) {
        printf("login called\n");
        return 0;
}
int app_logout(int argc, char** argv) {
        printf("Logout called\n");
        return 0;
}
int app_reset(int argc, char** argv) {
        printf("Reset called\n");
        return 0;
}
int app_exit(int argc, char** argv) {
        printf("Exit called\n");
        return 1;
}
static const struct cmd s_cmds[] = {
        { "help",        help },
        { "init",        app_init },
        { "login",       app_login },
        { "logout",      app_logout },
        { "reset",       app_reset },
        { "exit",       app_exit},
#if 0
        { "remove-key",  remove_key },
        { "list",        hsm_list },
        { "rand",        get_rand },
        { "derive",      derive_key },
        { "get-pubkey",  get_pubkey },
        { "get-prikey",  get_prikey },
        { "import",      import_key },
        { "sign",        sign },
        { "verify",      verify },
        { "digest",      digest },
        { "hmac-digest", sign },
        { "hkdf",        hkdf },
        { "encrypt",     encrypt },
        { "decrypt",     decrypt },
        { "write",       write_data },
        { "read",        read_data },
        { "remove",      remove_data },
        { "fmc",         fmc_feature },
        { "gpio",        fmc_gpio },
#endif
        { NULL,       NULL}
};
int run(int nargs, char** argv) {
        struct cmd *p = s_cmds;
        int ret = 0;
        for(;p->name && strncmp(p->name, argv[0], strlen(p->name)); ++p);
        if(p->name) {
                ret = p->f(nargs, argv);
        }
        return ret;
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
