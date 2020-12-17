#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	pid_t childpid;
	childpid = fork();
	if(childpid == -1) {
		printf(" Failed to for..\n");
		return -1;
	}

	if (childpid == 0) {
		printf("In child process..\n");
		execl("/bin/ls", "ls", "-l", NULL);
		return 1;
	}

	if (childpid != wait(NULL)) {
		printf("Failed to wait\n");
	}
	printf("Child exited..\n");
}
