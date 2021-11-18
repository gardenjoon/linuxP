// ex1
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct mymsgbuf
{
    long mtype;
    char mtext[80];
};
int main(void)
{
    key_t key;
    int msgid;
    struct mymsgbuf mesg;
    key = ftok("keyfile", 1);
    msgid = msgget(key, IPC_CREAT | 0644);
    if (msgid == -1)
    {
        perror("msgget");
        exit(1);
    }
    mesg.mtype = 1;
    strcpy(mesg.mtext, "Message Q Test\n");
    if (msgsnd(msgid, (void *)&mesg, 80, IPC_NOWAIT) == -1)
    {
        perror("msgsnd");
        exit(1);
    }
    return 0;
}

// ex2
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct mymsgbuf
{
    long mtype;
    char mtext[80];
};
int main(void)
{
    struct mymsgbuf inmsg;
    key_t key;
    int msgid, len;

    key = ftok("keyfile", 1);
    if ((msgid = msgget(key, 0)) < 0)
    {
        perror("msgget");
        exit(1);
    }

    len = msgrcv(msgid, &inmsg, 80, 0, 0);
    printf("Received Msg = %s, Len=%d\n", inmsg.mtext, len);

    return 0;
}

// ex3
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void)
{
    key_t key;
    int msgid;
    key = ftok("keyfile", 1);
    msgid = msgget(key, IPC_CREAT | 0644);
    if (msgid == -1)
    {
        perror("msgget");
        exit(1);
    }
    printf("Before IPC_RMID\n");
    system("ipcs -q");
    msgctl(msgid, IPC_RMID, (struct msqid_ds *)NULL);
    printf("After IPC_RMID\n");
    system("ipcs -q");
    return 0;
}

// prac1
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct mymsgbuf
{
    long mtype;
    char mtext[80];
};

int main(void)
{
    key_t key;
    int msgid;
    struct mymsgbuf mesg;
    key = ftok("keyfile", 1);
    msgid = msgget(key, IPC_CREAT | 0644);
    if (msgid == -1)
    {
        perror("msgget");
        exit(1);
    }
    mesg.mtype = 1;
    strcpy(mesg.mtext, "Hanbit Message 1\n");
    if (msgsnd(msgid, (void *)&mesg, 80, IPC_NOWAIT) == -1)
    {
        perror("msgsnd");
        exit(1);
    }
    mesg.mtype = 3;
    strcpy(mesg.mtext, "Hanbit Message 3-1\n");
    if (msgsnd(msgid, (void *)&mesg, 80, IPC_NOWAIT) == -1)
    {
        perror("msgsnd");
        exit(1);
    }
    mesg.mtype = 3;
    strcpy(mesg.mtext, "Hanbit Message 3-2\n");
    if (msgsnd(msgid, (void *)&mesg, 80, IPC_NOWAIT) == -1)
    {
        perror("msgsnd");
        exit(1);
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct mymsgbuf
{
    long mtype;
    char mtext[80];
};
int main(void)
{
    struct mymsgbuf inmsg;
    key_t key;
    int msgid, len;

    key = ftok("keyfile", 1);
    if ((msgid = msgget(key, 0)) < 0)
    {
        perror("msgget");
        exit(1);
    }

    len = msgrcv(msgid, &inmsg, 80, 0, 0);
    printf("Received Msg = %s, Len=%d\n", inmsg.mtext, len);
    len = msgrcv(msgid, &inmsg, 80, 0, 0);
    printf("Received Msg = %s, Len=%d\n", inmsg.mtext, len);
    len = msgrcv(msgid, &inmsg, 80, 0, 0);
    printf("Received Msg = %s, Len=%d\n", inmsg.mtext, len);

    return 0;
}

// homework 1
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct mymsgbuf
{
    long mtype;
    char mtext[80];
};

int main(void)
{
    int fd1, fd2, n;
    char buf[256];

    key_t key;
    int msgid;
    struct mymsgbuf mesg;

    fd1 = open("unix.txt", O_CREAT, 0777);
    if (fd1 == -1)
    {
        perror("open");
        exit(1);
    }

    while ((n = read(fd1, buf, 256)) > 0)
    {
        continue;
    }
    close(fd1);

    key = ftok("keyfile", 1);
    msgid = msgget(key, IPC_CREAT | 0644);
    if (msgid == -1)
    {
        perror("msgget");
        exit(1);
    }
    mesg.mtype = 1;
    strcpy(mesg.mtext, buf);
    if (msgsnd(msgid, (void *)&mesg, 80, IPC_NOWAIT) == -1)
    {
        perror("msgsnd");
        exit(1);
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

struct mymsgbuf
{
    long mtype;
    char mtext[80];
};
int main(void)
{
    struct mymsgbuf inmsg;
    key_t key;
    int msgid, len;
    int fd;
    char *buf;

    key = ftok("keyfile", 1);
    if ((msgid = msgget(key, 0)) < 0)
    {
        perror("msgget");
        exit(1);
    }

    len = msgrcv(msgid, &inmsg, 80, 0, 0);

    fd = open("receive.txt", O_CREAT | O_WRONLY, 0777);
    if(fd == -1){
        perror("open");
        exit(1);
    }
    if(write(fd, inmsg.mtext, len) == -1) {
        perror("write");
        exit(1);
    }

    close(fd);

    return 0;
}

//homework2
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>

struct mymsgbuf
{
    long mtype;
    char mtext[2];
};

int main(void)
{
    key_t key;
    int msgid, i;
    struct mymsgbuf mesg;

    key = ftok("keyfile", 1);
    msgid = msgget(key, IPC_CREAT | 0644);
    if (msgid == -1)
    {
        perror("msgget");
        exit(1);
    }
    mesg.mtype = 1;

    i = 1;
    while (1) {
        sprintf(mesg.mtext, "%d", i);
        if (msgsnd(msgid, (void *)&mesg, 80, IPC_NOWAIT) == -1)
        {
            perror("msgsnd");
            exit(1);
        }
        sleep(1);
        i++;
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct mymsgbuf
{
    long mtype;
    char mtext[80];
};
int main(void)
{
    struct mymsgbuf inmsg;
    key_t key;
    int msgid, len;

    key = ftok("keyfile", 1);
    if ((msgid = msgget(key, 0)) < 0)
    {
        perror("msgget");
        exit(1);
    }
    while (1) {
        msgrcv(msgid, &inmsg, 80, 0, 0);
        printf("%s\n", inmsg.mtext);
    }

    return 0;
}