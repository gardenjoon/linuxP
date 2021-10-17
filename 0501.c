// ex 5-1
#include <unistd.h>
#include <stdio.h>
int main(void)
{
    printf("PID : %d\n", (int)getpid());
    printf("PPID : %d\n", (int)getppid());
    return 0;
}

// ex 5-2
#include <unistd.h>
#include <stdio.h>
int main(void)
{
    printf("PID : %d\n", (int)getpid());
    printf("PGRP : %d\n", (int)getpgrp());
    printf("PGID(0) : %d\n", (int)getpgid(0));
    printf("PGID(2287) : %d\n", (int)getpgid(2287));
    return 0;
}

// ex 5-3
#include <unistd.h>
#include <stdio.h>
int main(void)
{
    printf("PID : %d\n", (int)getpid());
    printf("PGID : %d\n", (int)getpgrp());
    printf("SID : %d\n", (int)getsid(0));
    return 0;
}

// ex 5-4
#include <sys/types.h>
#include <sys/times.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void)
{
    double clck = sysconf(_SC_CLK_TCK);
    int i;
    time_t t;
    struct tms mytms;
    clock_t t1, t2;
    if ((t1 = times(&mytms)) == -1)
    {
        perror("times 1");
        exit(1);
    }
    for (i = 0; i < 999999; i++)
        time(&t);
    if ((t2 = times(&mytms)) == -1)
    {
        perror("times 2");
        exit(1);
    }
    printf("Real time : %.5f sec\n", (double)(t2 - t1) / clck);
    printf("User time : %.5f sec\n", (double)mytms.tms_utime / clck);
    printf("System time : %.5f sec\n", (double)mytms.tms_stime / clck);
    return 0;
}

// ex 5-5
#include <stdlib.h>
#include <stdio.h>
extern char **environ;
int main(void)
{
    char **env;
    env = environ;
    while (*env)
    {
        printf("%s\n", *env);
        env++;
    }
    return 0;
}

// ex 5-6
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
    char **env;

    env = envp;
    while (*env)
    {
        printf("%s\n", *env);
        env++;
    }

    return 0;
}

// ex 5-7
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    char *val;

    val = getenv("SHELL");
    if (val == NULL)
        printf("SHELL not defined\n");
    else
        printf("SHELL = %s\n", val);

    return 0;
}

// ex 5-8
#include <stdlib.h>
#include <stdio.h>
int main(void)
{
    char *val;

    val = getenv("SHELL");
    if (val == NULL)
        printf("SHELL not defined\n");
    else
        printf("1. SHELL = %s\n", val);

    putenv("SHELL=/usr/bin/csh");

    val = getenv("SHELL");
    printf("2. SHELL = %s\n", val);
    return 0;
}

// ex5-9
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    char *val;

    val = getenv("SHELL");
    if (val == NULL)
        printf("SHELL not defined\n");
    else
        printf("1. SHELL = %s\n", val);

    setenv("SHELL", "/usr/bin/csh", 0);
    val = getenv("SHELL");
    printf("2. SHELL = %s\n", val);

    setenv("SHELL", "/usr/bin/csh", 1);
    val = getenv("SHELL");
    printf("3. SHELL = %s\n", val);

    return 0;
}
