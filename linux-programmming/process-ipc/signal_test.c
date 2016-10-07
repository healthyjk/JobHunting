#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int ntimes = 0;

void main() {
    int pid, ppid;
    int p_action(), c_action();

    signal(SIGUSR1, p_action);
    switch(pid = fork()) {
    case -1:
        perror("synchro:");
        exit(1);
    case 0:
        signal(SIGUSR1, c_action);
        ppid = getppid();
        for(;;) {
            sleep(1);
            kill(ppid, SIGUSR1);
            pause();
        }
        break;
    default:
        for(;;) {
            pause();
            sleep(1);
            kill(pid, SIGUSR1);
        }
    }
}

p_action() {
    printf("parent caught signal #%d\n", ++ntimes);
}


c_action() {
    printf("child caught signal #%d\n", ++ntimes);
}
