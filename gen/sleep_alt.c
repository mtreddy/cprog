#include<stdio.h>
#include<sys/time.h>

#define delay_loop(x) ( { int i = 0;  for( i=0; i< x; i++); }  )
struct timeval ts;
int main()
{
    int ret = 0;
    ret =  gettimeofday(&ts, NULL);
    printf("\ntv_sec=%d tv_usec=%d\n", ts.tv_sec, ts.tv_usec);
    //sleep(1);
    delay_loop(0xFFFFFFF);
    ret =  gettimeofday(&ts, NULL);
    printf("\ntv_sec=%d tv_usec=%d\n", ts.tv_sec, ts.tv_usec);
}

