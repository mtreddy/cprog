#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/termios.h>    /* for winsize */

#include "db.h"


int main(void)
{

    DB *db1;


    db1 = db_open("./db1.first", O_RDWR, FILE_MODE);

    if(db1 == NUL)
        printf("Could not open data base.\n");
    else
        printf("Successfully created DB.\n");

    db_close(db);
}
