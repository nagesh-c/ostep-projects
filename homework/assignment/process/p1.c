#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	pid_t pid = 0;
	int x = 100;

	pid = fork();
	if (pid < 0) {
		printf("fork failed\n");
		exit(-1);
	} else if (pid == 0)
		printf("child process: value of x: %d %d\n", x, getppid());
	else
		printf("parent process: value of x: %d %d\n", x, getpid());
}
