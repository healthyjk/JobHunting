#include <stdio.h>
#include <unistd.h>
#include <syslog.h>
#include <time.h>
#include <signal.h>

#define MAXFD 64

void daemon_init(const char* pname, int facility) {
	int i;
	pid_t pid;

	/*exit parent process*/
	if (pid = fork()) {
		exit(0);
	}

	setsid();

	signal(SIGHUP, SIG_IGN);

	if (pid = fork()) {
		exit(0);
	}

	//daemon_proc = 1;

    /*注意此处切换的目录应为当前用户拥有权限的目录*/
	chdir("/tmp");

	umask(0);

	for (i = 0; i < MAXFD; ++i) {
		close(i);
	}

	//openlog(pname, LOG_PID, facility);
}

void main() {
	FILE *fp;
    time_t t;
    int i;
    daemon_init("my-daemon", 1);
    while(1) {
        sleep(1);
        fp = fopen("test.log", "a");
        
        if (fp >= 0) {
            time(&t);
            fprintf(fp, "current time is：%s\n", asctime(localtime(&t)));
            fclose(fp);
        }
        i++;
    }
    return;
}
