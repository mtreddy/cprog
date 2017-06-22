#include<stdio.h>
#include<string.h>

int main(int argc, char** argv)
{
    if(argc <= 1) {
        printf("Invalid args. "
                "read_date_str year=1000 month=12 date=12\n");
        return;
    }
    printf("command: %s %s\n",argv[1],argv[2]);

    int year=0, month=0, date=0;


    if(!strncmp("year",argv[1],4))
        sscanf(argv[1], "year=%d", &year);
    else {
        printf("Not a valid year\n");
        return;
    }
    if(argv[2] != NULL) {
    if(!strncmp("month",argv[2],4))
        sscanf(argv[2], "month=%d", &month);
    }

    if(argv[3] != NULL) {
    if(!strncmp("date",argv[3],4))
        sscanf(argv[3], "date=%d", &date);
    }

    printf("Year %d month %d day %d\n",year, month, date);

}
