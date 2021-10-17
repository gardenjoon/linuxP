// // ex 5-1
// #include <unistd.h>
// #include <stdio.h>
// int main(void)
// {
//     printf("PID : %d\n", (int)getpid());
//     printf("PPID : %d\n", (int)getppid());
//     return 0;
// }

// // ex 5-2
// #include <unistd.h>
// #include <stdio.h>
// int main(void)
// {
//     printf("PID : %d\n", (int)getpid());
//     printf("PGRP : %d\n", (int)getpgrp());
//     printf("PGID(0) : %d\n", (int)getpgid(0));
//     printf("PGID(2287) : %d\n", (int)getpgid(2287));
//     return 0;
// }

// // ex 5-3
// #include <unistd.h>
// #include <stdio.h>
// int main(void)
// {
//     printf("PID : %d\n", (int)getpid());
//     printf("PGID : %d\n", (int)getpgrp());
//     printf("SID : %d\n", (int)getsid(0));
//     return 0;
// }

// // ex 5-4
// #include <sys/types.h>
// #include <sys/times.h>
// #include <time.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// int main(void)
// {
//     double clck = sysconf(_SC_CLK_TCK);
//     int i;
//     time_t t;
//     struct tms mytms;
//     clock_t t1, t2;
//     if ((t1 = times(&mytms)) == -1)
//     {
//         perror("times 1");
//         exit(1);
//     }
//     for (i = 0; i < 999999; i++)
//         time(&t);
//     if ((t2 = times(&mytms)) == -1)
//     {
//         perror("times 2");
//         exit(1);
//     }
//     printf("Real time : %.5f sec\n", (double)(t2 - t1) / clck);
//     printf("User time : %.5f sec\n", (double)mytms.tms_utime / clck);
//     printf("System time : %.5f sec\n", (double)mytms.tms_stime / clck);
//     return 0;
// }

// // ex 5-5
// #include <stdlib.h>
// #include <stdio.h>
// extern char **environ;
// int main(void)
// {
//     char **env;
//     env = environ;
//     while (*env)
//     {
//         printf("%s\n", *env);
//         env++;
//     }
//     return 0;
// }

// // ex 5-6
// #include <stdio.h>

// int main(int argc, char **argv, char **envp)
// {
//     char **env;

//     env = envp;
//     while (*env)
//     {
//         printf("%s\n", *env);
//         env++;
//     }

//     return 0;
// }

// // ex 5-7
// #include <stdlib.h>
// #include <stdio.h>

// int main(void)
// {
//     char *val;

//     val = getenv("SHELL");
//     if (val == NULL)
//         printf("SHELL not defined\n");
//     else
//         printf("SHELL = %s\n", val);

//     return 0;
// }

// // ex 5-8
// #include <stdlib.h>
// #include <stdio.h>
// int main(void)
// {
//     char *val;

//     val = getenv("SHELL");
//     if (val == NULL)
//         printf("SHELL not defined\n");
//     else
//         printf("1. SHELL = %s\n", val);

//     putenv("SHELL=/usr/bin/csh");

//     val = getenv("SHELL");
//     printf("2. SHELL = %s\n", val);
//     return 0;
// }

// // ex5-9
// #include <stdlib.h>
// #include <stdio.h>

// int main(void)
// {
//     char *val;

//     val = getenv("SHELL");
//     if (val == NULL)
//         printf("SHELL not defined\n");
//     else
//         printf("1. SHELL = %s\n", val);

//     setenv("SHELL", "/usr/bin/csh", 0);
//     val = getenv("SHELL");
//     printf("2. SHELL = %s\n", val);

//     setenv("SHELL", "/usr/bin/csh", 1);
//     val = getenv("SHELL");
//     printf("3. SHELL = %s\n", val);

//     return 0;
// }

//prac 5-1
//명령행 인자로 PID를 입력받아 해당 프로세스가 속한 프로세스 그룹 ID(PGID)와 
//세션 ID를 출력하는 프로그램을 작성하라. 
//명령행 인자로 지정한 PID가 0이면 현재 프로세스를 대상으로 PGID와 세션ID를 구하라
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int num = atoi(argv[1]);
    printf("PGID : %d\n", (int)getpgid(num));
    printf("SID: %d\n", (int)getsid(num));

    return 0;
}


//prac 5-2
//다음과 같이 파이프로 연결한 프로세스 그룹에서 PGID를 구하는 프로그램을 작성하라.
// # sleep 100 | sleep 150 | sleep 200 &

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int num = atoi(argv[1]);
    printf("sleep 100 PGID : %d\n", (int)getpgid(num));
    printf("sleep 200 PGID: %d\n", (int)getpgid(num+1));
    printf("sleep 300 PGID: %d\n", (int)getpgid(num+2));
    return 0;
}

//prac 5-3
//다음과 같이 프로그램에서 sleep함수를 사용해 5초 동안 잠들게 했을 때 전체 수행 시간은 어떻게 되는가?
/*
#include <stdio.h>

int main(void) {
    sleep(5);
    return 0;
}
*/
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
    struct tms mytms;
    clock_t t1, t2;
    if ((t1 = times(&mytms)) == -1)
    {
        perror("times 1");
        exit(1);
    }

    sleep(5);

    if ((t2 = times(&mytms)) == -1)
    {
        perror("times 2");
        exit(1);
    }
    printf("time : %.1f sec\n", (double)(t2 - t1) / clck);
    return 0;
}

//prac 5-4
// 반복문을 사용해 1~10000까지 더하면서 결과값을 반복적으로 출력하는 프로그램을 작성하고, 
// 이 프로그램의 실행 시간을 측정하라.
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
    int sum = 0;
    struct tms mytms;
    clock_t t1, t2;
    if ((t1 = times(&mytms)) == -1)
    {
        perror("times 1");
        exit(1);
    }
    while (sum != 1000000){
        sum++;
        printf("sum : %d\n", sum);
    }
    if ((t2 = times(&mytms)) == -1)
    {
        perror("times 2");
        exit(1);
    }
    printf("time : %.1f sec\n", (double)(t2 - t1) / clck);
    return 0;
}

//prac 5-5
// 환경변수 HBENV를 새로 정의하고 값을 hbooks로 설정하는 프로그램을 작성하라.

#include <stdlib.h>
#include <stdio.h>

int main(void) {
    char *val;
    setenv("HBENV", "hbooks", 1);
    val = getenv("HBENV");
    printf("HBENV = %s\n", val);

    return 0;
}

//prac 5-6
//연습문제 5번에 MYENV 변수를 삭제하는 기능을 넣어 프로그램을 수정하라.
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    char *val;
    setenv("HBENV", "hbooks", 1);
    val = getenv("HBENV");
    printf("HBENV = %s\n", val);
    unsetenv("MYENV");
    val = getenv("MYENV");
    printf("MYENV = %s\n", val);

    return 0;
}

//prac 5-7
//명령행 인자로 환경 변수명과 값을 입력받아 환경 변수를 설정하는 프로그램을 작성하라.
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    setenv(argv[1], argv[2], 1);
    char *val;
    val = getenv(argv[1]);
    printf("%s = %s\n", argv[1], val);
    return 0;
}