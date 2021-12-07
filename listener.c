#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define KEY 1005
#define START_FLAG 1
#define END_FLAG 0

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

int main(void)
{
    int semid;
    int shmid, i;
    char *shmaddr;

    if ((semid = initsem(1)) < 0)
        exit(1);
    shmid = shmget((key_t)KEY, 1024, IPC_CREAT | 0666);
    shmaddr = (char *)shmat(shmid, (void *)NULL, 0);
    shmaddr[0] = 2;

    while (1)
    {
        if (shmaddr[0] == START_FLAG)
        {
            for (i = 0; i < 20; i++)
            {
                semlock(semid);
                sprintf(shmaddr, "%s", "PKNU");
                sleep(1);
                printf("%s\n", shmaddr);
                semunlock(semid);
            }
            shmaddr[0] = END_FLAG;
        }

        if (shmaddr[0] == END_FLAG)
        {
            shmctl(shmid, IPC_RMID, NULL);
            return 0;
        }
        
    }

    return 0;
}
