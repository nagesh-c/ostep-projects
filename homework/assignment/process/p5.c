#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	pid_t pid = 0;

	pid = fork();
	if (pid < 0) {
		exit(-1);
	} else if (0 == pid) {
		pid_t childpid = 0;
		int pipe_fd[2];
		if (pipe(pipe_fd)) {
			printf("pipe creation failed\n");
			exit(-1);
		}
		childpid = fork();
		if (childpid < 0) {
			exit(-1);
		} else if (childpid == 0) {
			close(pipe_fd[0]);
			// As a rule of thumb, once the file descriptor is
			// duped for stdout/stdin close the fd returned by pipe.
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
			execlp("cat", "cat", "p1.c", NULL);
		} else {
			close(pipe_fd[1]);
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);
			wait(&childpid);
			execlp("wc", "wc", "-l", NULL);
		}
	}  else {
		wait(&pid);
	}
}
