#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

int main()
{
    int rc1 = 0;
    char cmd_str[200];
    char eth3_ip[] = "10.1.1.2";
    char eth3_mac[] = "60:73:5c:fe:ed:b9";

    sprintf(cmd_str, "nping -e eth2 --send-eth --dest-ip %s -p 1000 -g 1000  --dest-mac  %s --tcp --rate 300 -c 100 > /tmp/ge_trf.txt",
            eth3_ip, eth3_mac);
    printf("eth2 trf str: %s\n", cmd_str);
    rc1 = system(cmd_str);
}
