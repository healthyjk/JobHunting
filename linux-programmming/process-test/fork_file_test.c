#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void failure(char* s) {
	perror(s);
	exit(1);
}

void printpos(char* string, int fildes) {
	long pos;
	pos = lseek(fildes, 0L, 1);
	if (pos < 0L) {
		failure("lseek failed:");
	}
	printf("%s : %ld\n", string, pos);
}

void main() {
	int fd;
	int pid;
	char buf[10];
	if ((fd = open("data.txt", O_RDONLY)) < 0) {
		failure("open failed:");
	}
	lseek(fd, 0L, 0);
	printf("fd:%d\n", fd);
	read(fd, buf, 10);

	buf[10] = '\0';
	printf("buf:%s\n", buf);

	printpos("Before fork", fd);

	if ((pid=fork()) < 0) {
		close(fd);
		failure("fork failed:");
	}	else if (!pid) {
		printpos("child before read", fd);
		read(fd, buf, 10);

		buf[10] = '\0';
		printf("buf:%s\n", buf);

		printpos("child after read", fd);
	} else {
		wait(NULL);
		printpos("parent after wait", fd);
	}
	close(fd);
}
