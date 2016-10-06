#include <stdio.h>
#include <unistd.h>
void main()
{
	printf("Executing ls\n");
	execl("/bin/ls", "ls", "-l", NULL);
	/* 如果 execl 返回,说明调用失败 */
	printf("execl failed to run ls\n");
	exit(1);
}
