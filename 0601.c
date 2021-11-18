// ex 6-1
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int a;
    a = system("ps ‐ef | grep han > han.txt");
    printf("Return Value : %d\n", a);

    return 0;
}

// ex 6-2
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(void) {
    pid_t pid;

    switch (pid = fork()) {
    case -1: /* fork failed */
        perror("fork");
        exit(1);
        break;
    case 0: /* child process */
        printf("Child Process ‐ My PID:%d, My Parent's PID:%d\n",
               (int)getpid(), (int)getppid());
        break;
    default: /* parent process */
        printf("Parent process ‐ My PID:%d, My Parent's PID:%d, My Child's PID:%d\n", (int)getpid(), (int)getppid(), (int)pid);
        break;
    }

    printf("End of fork\n");
    return 0;
}

// ex6-3
#include <stdlib.h>
#include <stdio.h>

void cleanup1(void) {
    printf("Cleanup 1 is called.\n");
}

void cleanup2(void) {
    printf("Cleanup 2 is called.\n");
}

int main(void) {
    atexit(cleanup1);
    atexit(cleanup2);

    exit(0);
}

// ex6-4
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    printf("‐‐> Before exec function\n");

    if (execlp("ls", "ls", "‐a", (char *)NULL) == -1) {
        perror("execlp");
        exit(1);
    }

    printf("-‐> After exec function\n");

    return 0;
}

// ex6-5
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    char *argv[3];

    printf("Before exec function\n");

    argv[0] = "ls";
    argv[1] = "‐a";
    argv[2] = NULL;
    if (execv("/usr/bin/ls", argv) == -1) {
        perror("execv");
        exit(1);
    }

    printf("After exec function\n");

    return 0;
}

// ex6-6
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(void) {
    char *argv[3];
    char *envp[2];

    printf("‐‐> Before exec function\n");

    argv[0] = "arg.out";
    argv[1] = "100";
    argv[2] = NULL;

    envp[0] = "MYENV=Pukyong";
    envp[1] = NULL;

    if (execve("./arg.out", argv, envp) == -1) {
        perror("execve");
        exit(1);
    }

    printf("After exec function\n");

    return 0;
}

// ex6-6
#include <stdio.h>

int main(int argc, char **argv, char **envp) {
    int n;
    char **env;

    printf("\n‐‐> In ex6_6_arg.c Main\n");
    printf("argc = %d\n", argc);
    for (n = 0; n < argc; n++)
        printf("argv[%d] = %s\n", n, argv[n]);

    env = envp;
    while (*env) {
        printf("%s\n", *env);
        env++;
    }

    return 0;
}

// 6-7
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(void) {
    pid_t pid;

    switch (pid = fork()) {
    case -1: /* fork failed */
        perror("fork");
        exit(1);
        break;
    case 0: /* child process */
        printf("‐‐> Child Process\n");
        if (execlp("ls", "ls", "‐a", (char *)NULL) == -1)
     {
            perror("execlp");
            exit(1);
        }
        exit(0);
        break;
    default: /* parent process */
        printf("‐‐> Parent process ‐ My PID:%d\n", (int)getpid());
        break;
    }
    return 0;
}

// 6-8
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
int main(void) {
    int status;
    pid_t pid;
    switch (pid = fork()) {
    case -1: /* fork failed */
        perror("fork");
        exit(1);
        break;
    case 0: /* child process */
        printf("‐‐> Child Process\n");
        exit(2);
        break;
    default: /* parent process */
        while (wait(&status) != pid)
            continue;
        printf("‐‐> Parent process\n");
        printf("Status: %d, %x\n", status, status);
        printf("Child process Exit Status:%d\n", status >> 8);
        break;
    }
    return 0;
}

// ex6-9
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(void) {
    int status;
    pid_t pid;

    if ((pid = fork()) < 0){ /* fork failed */
        perror("fork");
        exit(1);
    }

    if (pid == 0){ /* child process */
        printf("‐‐> Child process\n");
        sleep(3);
        exit(3);
    }

    printf("‐‐> Parent process\n");

    while (waitpid(pid, &status, WNOHANG) == 0) {
        printf("Parent still wait...\n");
        sleep(1);
    }

    printf("Child Exit Status : %d\n", status >> 8);

    return 0;
}