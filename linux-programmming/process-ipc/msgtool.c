/*************************************************************************
* File Name: msgtool2.c
* Author: yanjiankang
* Description: program function
* Mail: healthyjk@gmail.com 
* Created Time: 2016年10月07日 星期五 23时14分11秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <ctype.h>

#define MAX_SEND_SIZE 80

struct mymsgbuf {
    long mtype;
    char mtext[MAX_SEND_SIZE];
};

void send_message(int qid, struct mymsgbuf* qbuf, long type, char* text);
void read_message(int qid, struct mymsgbuf* qbuf, long type);
void remove_queue(int qid);
void change_queue_mode(int qid, char* mode);
void usage(void);

int main(int argc, char* argv[]) {
    key_t key;
    int msgqueue_id;
    struct mymsgbuf qbuf;

    if (argc == 1) {
        usage();
    }

    key = ftok(".", 'm');

    /*open the queue*/
    if ((msgqueue_id = msgget(key, IPC_CREAT|0660)) == -1) {
        perror("msgget");
        exit(1);
    }

    switch(tolower(argv[1][0])) {
        case 's': send_message(msgqueue_id, (struct mymsgbuf*)&qbuf, atol(argv[2]), argv[3]);
                  break;
        case 'r': read_message(msgqueue_id, &qbuf, atol(argv[2]));
                  break;
        case 'd': remove_queue(msgqueue_id);
                  break;
        case 'm': change_queue_mode(msgqueue_id, argv[2]);
                  break;
        default : usage(); break;
    }
    return;
}


void send_message(int qid, struct mymsgbuf* qbuf, long type, char* text) {
    printf("Send a message...\n");
    qbuf->mtype = type;
    strcpy(qbuf->mtext, text);

    if (msgsnd(qid, (struct mymsgbuf*)qbuf, strlen(qbuf->mtext)+1, 0) == -1) {
        perror("msgsnd");
        exit(1);
    }
}

void read_message(int qid, struct mymsgbuf* qbuf, long type) {
    printf("Reading a message...\n");
    qbuf->mtype = type;
    msgrcv(qid, (struct mymsgbuf*)qbuf, MAX_SEND_SIZE, type, 0);
    printf("Type:%ld, Text:%s\n", qbuf->mtext, qbuf->mtext);
}

void remove_queue(int qid) {
    msgctl(qid, IPC_RMID, 0);
}

void change_queue_mode(int qid, char* mode) {
    struct msqid_ds myqueue_ds;

    /*Get current info*/
    msgctl(qid, IPC_STAT, &myqueue_ds);

    /*convert and load the mode*/
    sscanf(mode, "%ho", &myqueue_ds.msg_perm.mode);

    /*update the mode*/
    msgctl(qid, IPC_SET, &myqueue_ds);
}

void usage(void) {
    fprintf(stderr, "msgtool - A utility for tinkering with msg queue\n");
    fprintf(stderr, "\nUsage: msgtool (s)end <type> <messagetext>\n");
    fprintf(stderr, "                 (r)ecv <type>\n");
    fprintf(stderr, "                 (d)elete\n");
    fprintf(stderr, "                 (m)ode <octal mode>\n");
    exit(1);
}
