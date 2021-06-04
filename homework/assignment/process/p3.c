#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	pid_t pid = 0;

	pid = fork();
	if (pid < 0) {
		printf("fork failed\n");
		exit(1);
	} else if (pid == 0) {
		// child process
		char *args[4] = {NULL};
		args[0] = strdup("/bin/ls");
		args[1] = strdup("-lart");
		execve(args[0], args, NULL);
		// this is not executed
		//execl("/bin/ls", "/bin/ls", "-l", (char *)0);
	} else {
		// parent process
		wait(&pid);
	}
}
