#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static int num = 0;
static char namebuf[20];
static char prefix[] = "/tmp/tmp_";

void itoa(int i, char* string) {
	int power, j;
	j = i;
	for (power = 1; j >= 10; j /= 10) {
		power *= 10;
	}

	for (; power > 0; power /= 10) {
		*string++ = '0' + i/power;
		i %= power;
	}
}

void clearStr(char* str) {
	while (*str != '\0') {
		*str++ = '\0';
	}
}

char* gettemp() {
	int length, pid;
	pid = getpid();
	clearStr(namebuf);
	strcpy(namebuf, prefix);
	length = strlen(namebuf);
	//printf("num:%d, namebuf: %s, length:%d\n", num, namebuf, length);

	itoa(pid, &namebuf[length]);
	strcat(namebuf, ".");
	length = strlen(namebuf);

	do {
		itoa(num++, &namebuf[length]);
	} while (access(namebuf, 0) != -1);

	return namebuf;
}

void main() {
	char* file_name;
  int i;
	for (i = 0; i < 20; ++i) {
		file_name = gettemp();
		printf("file name:%s\n", file_name);
	}
}
