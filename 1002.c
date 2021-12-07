// ex4
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    key_t key;
    int shmid;

    key = ftok("shmfile", 1);
    shmid = shmget(key, 1024, IPC_CREAT | 0644);
    if (shmid == -1)
    {
        perror("shmget");
        exit(1);
    }

    return 0;
}

// ex5
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int shmid, i;
    char *shmaddr, *shmaddr2;

    shmid = shmget(IPC_PRIVATE, 20, IPC_CREAT | 0644);
    if (shmid == -1)
    {
        perror("shmget");
        exit(1);
    }

    switch (fork())
    {
    case -1:
        perror("fork");
        exit(1);
        break;
    case 0:
        shmaddr = (char *)shmat(shmid, (char *)NULL, 0);
        printf("Child Process =====\n");
        for (i = 0; i < 10; i++)
            shmaddr[i] = 'a' + i;
        shmdt((char *)shmaddr);
        exit(0);
        break;
    default:
        wait(0);
        shmaddr2 = (char *)shmat(shmid, (char *)NULL, 0);
        printf("Parent Process =====\n");
        for (i = 0; i < 10; i++)
            printf("%c ", shmaddr2[i]);
        printf("\n");
        sleep(5);
        shmdt((char *)shmaddr2);
        shmctl(shmid, IPC_RMID, (struct shmid_ds *)NULL);
        break;
    }

    return 0;
}

// ex6 s
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

void handler(int dummy)
{
    ;
}

int main(void)
{
    key_t key;
    int shmid;
    void *shmaddr;
    char buf[1024];
    sigset_t mask;
    struct sigaction act_new;
    act_new.sa_handler = handler;

    key = ftok("shmfile", 1);
    shmid = shmget(key, 1024, IPC_CREAT | 0666);

    sigfillset(&act_new.sa_mask);
    sigdelset(&act_new.sa_mask, SIGUSR1);
    sigprocmask(SIG_SETMASK, &act_new.sa_mask, NULL);
    sigaction(SIGUSR1, &act_new, NULL);
    sigset(SIGUSR1, handler);

    printf("Listener wait for Talker\n");
    sigsuspend(&mask);

    printf("Listener Start =====\n");
    shmaddr = shmat(shmid, NULL, 0);
    strcpy(buf, shmaddr);
    printf("Listener received : %s\n", buf);

    strcpy(shmaddr, "Have a nice day\n");
    sleep(3);
    shmdt(shmaddr);

    return 0;
}
// ex6 c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>


int main(int argc, char **argv)
{
    key_t key;
    int shmid;
    void *shmaddr;
    char buf[1024];

    key = ftok("shmfile", 1);
    shmid = shmget(key, 1024, 0);

    shmaddr = shmat(shmid, NULL, 0);
    strcpy(shmaddr, "Hello, I'm talker\n");

    kill(atoi(argv[1]), SIGUSR1);
    sleep(2);
    strcpy(buf, shmaddr);

    printf("Listener said : %s\n", buf);
    system("ipcs -m");
    shmdt(shmaddr);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

// ex7
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <errno.h>

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int initsem(key_t semkey)
{
    union semun semunarg;
    int status = 0, semid;

    semid = semget(semkey, 1, IPC_CREAT | IPC_EXCL | 0600);
    if (semid == -1)
    {
        if (errno == EEXIST)
            semid = semget(semkey, 1, 0);
    }
    else
    {
        semunarg.val = 1;
        status = semctl(semid, 0, SETVAL, semunarg);
    }

    if (semid == -1 || status == -1)
    {
        perror("initsem");
        return (-1);
    }

    return semid;
}

int semlock(int semid)
{
    struct sembuf buf;

    buf.sem_num = 0;
    buf.sem_op = -1;
    buf.sem_flg = SEM_UNDO;
    if (semop(semid, &buf, 1) == -1)
    {
        perror("semlock failed");
        exit(1);
    }
    return 0;
}

int semunlock(int semid)
{
    struct sembuf buf;

    buf.sem_num = 0;
    buf.sem_op = 1;
    buf.sem_flg = SEM_UNDO;
    if (semop(semid, &buf, 1) == -1)
    {
        perror("semunlock failed");
        exit(1);
    }
    return 0;
}
void semhandle()
{
    int semid;
    pid_t pid = getpid();

    if ((semid = initsem(1)) < 0)
        exit(1);

    printf("Lock : Process %d\n", (int)pid);
    printf("** Lock Mode : Critical Section\n");
    sleep(1);
    printf("Unlock : Process %d\n", (int)pid);

    exit(0);
}

int main(void)
{
    int a;
    for (a = 0; a < 3; a++)
        if (fork() == 0)
            semhandle();

    return 0;
}

//prac2
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

void handler(int dummy)
{
    ;
}

int main(void)
{
    key_t key;
    int shmid;
    void *shmaddr;
    char buf[1024];
    sigset_t mask;
    struct sigaction act_new;
    act_new.sa_handler = handler;

    key = ftok("shmfile", 1);
    shmid = shmget(key, 1024, IPC_CREAT | 0666);

    sigfillset(&act_new.sa_mask);
    sigdelset(&act_new.sa_mask, SIGUSR1);
    sigprocmask(SIG_SETMASK, &act_new.sa_mask, NULL);
    sigaction(SIGUSR1, &act_new, NULL);
    sigset(SIGUSR1, handler);

    printf("Listener wait for Talker\n");
    sigsuspend(&mask);

    printf("Listener Start =====\n");
    shmaddr = shmat(shmid, NULL, 0);
    strcpy(buf, shmaddr);
    printf("Listener received : %s\n", buf);

    if (buf == "q") {
        return 0;
    }

    sleep(3);
    shmdt(shmaddr);

    return 0;
}

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>


int main(int argc, char **argv)
{
    key_t key;
    int shmid, i;
    char *shmaddr;
    char buf[1024];

    key = ftok("shmfile", 1);
    shmid = shmget(key, 1024, 0);

    for (i = 0; i<31; i++) {
        shmaddr = (char *)shmat(shmid, (char *)NULL, 0);
        shmaddr[i] = 'a' + i;
        strcpy(shmaddr, shmaddr);

        kill(atoi(argv[1]), SIGUSR1);
        sleep(2);
    }
    shmdt(shmaddr);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}