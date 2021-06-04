#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
	pid_t pid = 0;
	int fd, bytes_written = 0;
	char str[100] = {'\0'};

	fd = open("./tmp.txt", O_WRONLY | O_CREAT, S_IRWXU);
	if (fd < 0) {
		printf("file open failed\n");
		exit(1);
	}

	pid = fork();
	if (pid < 0) {
		printf("fork failed\n");
		exit(-1);
	} else if (pid == 0) {
		sprintf(str, "helloworld!! by %d", getpid());
		bytes_written = write(fd, str, strlen(str));
		close(fd);
		printf("child process: %d %d\n", bytes_written, getpid());
	} else {
		sprintf(str, "helloworld by %d", getpid());
		bytes_written = write(fd, str, strlen(str));
		bytes_written += write(fd, str, strlen(str));
		close(fd);
		printf("parent process: %d %d\n", bytes_written, getpid());
	}
}
