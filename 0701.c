// ex1
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int main(void)
{
    printf("Before SIGCONT Signal to parent.\n");
    kill(getppid(), SIGCONT);

    printf("Before SIGQUIT Signal to me.\n");

    kill(getpid(), SIGQUIT);

    printf("After SIGQUIT Signal.\n");

    return 0;
}

// ex2
#include <signal.h>
void handler(int signo)
{
    printf("Signal Handler Signal Number : %d\n", signo);
    psignal(signo, "Received Signal");
}
int main(void)
{
    void (*hand)(int);
    hand = signal(SIGINT, handler);
    if (hand == SIG_ERR)
    {
        perror("signal");
        exit(1);
    }
    printf("Wait 1st Ctrl+C... : SIGINT\n");
    pause();
    printf("After 1st Signal Handler\n");
    printf("Wait 2nd Ctrl+C... : SIGINT\n");
    pause();
    printf("After 2nd Signal Handler\n");

    return 0;
}

// ex3
#include <signal.h>
void handler(int signo)
{
    void (*hand)(int);
    hand = signal(SIGINT, handler);
    if (hand == SIG_ERR)
    {
        perror("signal");
        exit(1);
    }
    printf("Signal Handler Signal Number: %d\n", signo);
    psignal(signo, "Received Signal");
}

// ex4
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int signo)
{
    printf("Signal Handler Signal Number : %d\n", signo);
    psignal(signo, "Received Signal");
}

int main(void)
{
    void (*hand)(int);
    hand = signal(SIGINT, handler);

    if (hand == SIG_ERR)
    {
        perror("signal");
        exit(1);
    }
    printf("Wait 1st Ctrl+C... : SIGINT\n");
    pause();
    printf("After 1st Signal Handler\n");
    printf("Wait 2nd Ctrl+C... : SIGINT\n");
    pause();
    printf("After 2nd Signal Handler\n");
    return 0;
}

// ex5
#include <signal.h>
#include <stdio.h>

int main(void)
{
    sigset_t st;

    sigemptyset(&st);
    sigaddset(&st, SIGINT);
    sigaddset(&st, SIGQUIT);

    if (sigismember(&st, SIGINT))
        printf("SIGINT is setting.\n");

    printf("** Bit Pattern: %x\n", st.__val[0]);

    return 0;
}

// ex6
#include <signal.h>
#include <stdio.h>

void handler(int signo)
{
    psignal(signo, "Received Signal:");
    sleep(5);
    printf("In Signal Handler, After Sleep\n");
}

int main(void)
{
    struct sigaction act;

    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGQUIT);
    act.sa_flags = 0;
    act.sa_handler = handler;
    if (sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0)
    {
        perror("sigaction");
        exit(1);
    }
    fprintf(stderr, "Input SIGINT: ");
    pause();
    fprintf(stderr, "After Signal Handler\n");

    return 0;
}

// ex7
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int signo)
{
    psignal(signo, "Received Signal:");
    sleep(5);
    printf("In Signal Handler, After Sleep\n");
}
int main(void)
{
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGQUIT);
    act.sa_flags = SA_RESETHAND;
    act.sa_handler = handler;
    if (sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0)
    {
        perror("sigaction");
        exit(1);
    }
    fprintf(stderr, "Input SIGINT: ");
    pause();

    fprintf(stderr, "After Signal Handler\n");
    return 0;
}

// ex8
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int signo, siginfo_t *sf, ucontext_t *uc)
{
    psiginfo(sf, "Received Signal:");
    printf("si_code : %d\n", sf->si_code);
}
int main(void)
{
    struct sigaction act;
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = (void (*)(int, siginfo_t *, void *))handler;
    sigemptyset(&act.sa_mask);
    if (sigaction(SIGUSR1, &act, (struct sigaction *)NULL) < 0)
    {
        perror("sigaction");
        exit(1);
    }

    pause();
    return 0;
}

// ex9
#include <unistd.h>
#include <signal.h>
// #include <siginfo.h>
#include <stdio.h>
void handler(int signo)
{
    psignal(signo, "Received Signal");
}
int main(void)
{
    sigset(SIGALRM, handler);

    alarm(2);
    printf("Wait...\n");
    sleep(3);

    return 0;
}

// ex10
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
void handler()
{
    printf("Timer Invoked..\n");
}

int main(void)
{
    struct itimerval it;

    sigset(SIGALRM, handler);
    it.it_value.tv_sec = 3;
    it.it_value.tv_usec = 0;
    it.it_interval.tv_sec = 2;
    it.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &it, (struct itimerval *)NULL) == -1)
    {
        perror("setitimer");
        exit(1);
    }
    while (1)
    {
        if (getitimer(ITIMER_REAL, &it) == -1)
        {
            perror("getitimer");
            exit(1);
        }
        printf("%d sec, %d msec.\n", (int)it.it_value.tv_sec, (int)it.it_value.tv_usec);
        sleep(1);
    }
    return 0;
}

// ex11
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int signo)
{
    char *s;

    s = strsignal(signo);
    printf("Recieved Signal : %s\n", s);
}

int main(void)
{
    if (sigset(SIGINT, handler) == SIG_ERR)
    {
        perror("sigset");
        exit(1);
    }
    sighold(SIGINT);
    pause();
    return 0;
}

// ex12
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int main(void)
{
    sigset_t new;

    sigemptyset(&new);
    sigaddset(&new, SIGINT);
    sigaddset(&new, SIGQUIT);
    sigprocmask(SIG_BLOCK, &new, (sigset_t *)NULL);

    printf("Blocking Signals : SIGINT, SIGQUIT\n");
    printf("Send SIGQUIT\n");
    kill(getpid(), SIGQUIT);

    printf("UnBlocking Signals\n");

    sigprocmask(SIG_UNBLOCK, &new, (sigset_t *)NULL);

    return 0;
}

// ex13
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void handler(int signo)
{
    psignal(signo, "Received Signal: ");
}

int main(void)
{
    sigset_t set;

    sigset(SIGALRM, handler);

    sigfillset(&set);
    sigdelset(&set, SIGALRM);

    alarm(3);

    printf("Wait...\n");

    sigsuspend(&set);

    return 0;
}

//prac 2
#include <signal.h>
#include <stdio.h>

int main(void) {
    sigset_t st;
    sigemptyset(&st);

    sigaddset(&st, SIGQUIT);
    sigaddset(&st, SIGILL);
    sigaddset(&st, SIGTRAP);

    if (sigsismember(&st, SIGILL))
        printf("SIGILL is setting.\n");
    
    printf("** Bit Pattern: %lx\n", st.__val[0]);

    return 0;
}

//prac 3
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int signo)
{
    printf("Signal Handler Signal Number : %d\n", signo);
    psignal(signo, "Received Signal");
}

int main(void)
{
    if (sigset(SIGQUIT, handler) == SIG_ERR) {
        perror("sigset");
        exit(1);
    }

    printf("Wait 1st Ctrl+C... : SIGQUIT\n");
    pause();
    printf("After 1st Signal Handler\n");
    printf("Wait 2nd Ctrl+C... : SIGQUIT\n");
    pause();
    printf("After 2nd Signal Handler\n");

    return 0;
}

//prac4
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int signo)
{
    psignal(signo, "Received Signal:");
    sleep(5);
    printf("In Signal Handler, After Sleep\n");
}
int main(void)
{
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGQUIT);
    act.sa_flags = SA_RESETHAND;
    act.sa_handler = handler;
    if (sigaction(SIGQUIT, &act, (struct sigaction *)NULL) < 0)
    {
        perror("sigaction");
        exit(1);
    }
    fprintf(stderr, "Input SIGQUIT: ");
    pause();

    fprintf(stderr, "After Signal Handler\n");
    return 0;
}

//prac5
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int main(void)
{
    sigset_t new;

    sigemptyset(&new);
    sigaddset(&new, SIGINT);
    sigaddset(&new, SIGQUIT);
    
    while (1) {
        sigprocmask(SIG_BLOCK, &new, (sigset_t *)NULL);
        printf("Hanbit Books\n");
        sleep(1);
    }
    
    return 0;
}

//prac6
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
 
#define INTERVAL 1

void mytimer(int signo)
{
    sigset_t st;
    sigfillset(&st);
    sigprocmask(SIG_BLOCK, &st, (sigset_t *)NULL);
    sigrelse(SIGINT);
    printf("Wake up\n");
    alarm(INTERVAL); 
}
 
int main(void)
{
    struct sigaction act;
    act.sa_handler = mytimer;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
 
    sigaction(SIGALRM, &act, 0);
    alarm(INTERVAL);
 
    while(1);
    return 0;
}



//prac 7
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define INTERVAL 1

void timer(int signo)
{
        printf("Message\n");
        alarm(INTERVAL);
}

int main(void)
{
        struct sigaction act;

        act.sa_handler = timer;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;

        sigaction(SIGALRM, &act, 0);

        alarm(INTERVAL);

        while(1)
        {
            sleep(100);  
        }
}

