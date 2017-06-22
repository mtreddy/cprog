#include <stdio.h>
struct student {
    char name[50];
    int sub1;
    int sub2;
    int sub3;
}stu;
int main ()
{
    struct student st1 = {"Subba Rao", 30 + 35, 0x20 + 0x40, 90 + 1};
    printf("name %s \n sub1 = %d \n sub2 = %d \n sub3=%d\n", st1.name, st1.sub1, st1.sub2, st1.sub3);
}
