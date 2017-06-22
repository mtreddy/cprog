#include <stdio.h>
#include <string.h>
#include <fcntl.h>

typedef unsigned int uint32;
int main()
{
    char cmd_buf[500]; 
    uint32 retval=1;
    snprintf(cmd_buf, sizeof(cmd_buf) - 1,
            "/diag/bin/tib_td2_prbs.bash %d %d %d", 0xFFFFFF, 31, 10);
     FILE *fp; 

     int status; 
     char path[10000];
     /* Open the command for reading. */
     fp = popen(cmd_buf, "r");
      if (fp == NULL) { 
          printf("Failed to run command %s\n", cmd_buf);
          return 2;
      }

      //while (fgets(path, sizeof(path)-1, fp) > 0) {
      while (fgets(path, sizeof(path)-1, fp) != NULL) {
          printf("%s", path); 
          char *pch=NULL; 
          pch = strstr(path, "TIB-TD2 PRBS test PASS");
          if (pch)   {
              printf("-- \n");
          } else {
              printf("Buffer is empty..!!");
          }
          if(pch)
              retval = 0;
      }
      pclose(fp);
      return retval;

}
