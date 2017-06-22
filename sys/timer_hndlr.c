//gcc.c4.7.0-p1.x86_64 timer_hndlr.c  -o time
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

volatile int stop=0;

void sigalrm_handler( int sig )
{
    stop = 1;
    system("./tbded_reserv.sh");
    sleep(5);
    system(" /users/mareddy/bin/testbed_reserve.txt ");
    printf("Handler called....\n");
}
        
int send_a_packet(void) {
    sleep(1);
}

int main(int argc, char **argv)
{
    struct sigaction sact;
    int num_sent = 0;

    sigemptyset (&sact.sa_mask);
    sact.sa_flags = 0;
    sact.sa_handler = sigalrm_handler;
    sigaction(SIGALRM, &sact, NULL);

    alarm(5400);  /* Request SIGALRM in 90 mins or 5400 seconds */
    while (!stop) {
        send_a_packet();
        num_sent++;
    }

    printf("sent %d packets\n", num_sent);
    //exit(0);
}
