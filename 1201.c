// 1 server
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define PORTNUM 9001

int main(void)
{
    char buf[256];
    struct sockaddr_in sin, cli;
    int sd, ns, clientlen = sizeof(cli);

    memset((char *)&sin, '\0', sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORTNUM);
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }
    if (bind(sd, (struct sockaddr *)&sin, sizeof(sin)))
    {
        perror("bind");
        exit(1);
    }

    if (listen(sd, 5))
    {
        perror("listen");
        exit(1);
    }

    while (1)
    {
        if ((ns = accept(sd, (struct sockaddr *)&cli, &clientlen)) == -1)
        {
            perror("accept");
            exit(1);
        }
        sprintf(buf, "%s", inet_ntoa(cli.sin_addr));
        printf("*** Send a Message to Client(%s)\n", buf);

        strcpy(buf, "Welcome to Network Server!!!");
        if (send(ns, buf, strlen(buf) + 1, 0) == -1)
        {
            perror("send");
            exit(1);
        }
        if (recv(ns, buf, strlen(buf), 0) == -1)
        {
            perror("recv");
            exit(1);
        }

        printf("** From Client : %s\n", buf);
        close(ns);
    }
    close(sd);

    return 0;
}

// 1 client
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define PORTNUM 9001
int main(void)
{
    int sd;
    char buf[256];
    struct sockaddr_in sin;

    memset((char *)&sin, '\0', sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORTNUM);
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }
    if (connect(sd, (struct sockaddr *)&sin, sizeof(sin)))
    {
        perror("connect");
        exit(1);
    }
    if (recv(sd, buf, sizeof(buf), 0) == -1)
    {
        perror("recv");
        exit(1);
    }
    printf("** From Server : %s\n", buf);
    strcpy(buf, "I want a HTTP Service.");
    if (send(sd, buf, sizeof(buf) + 1, 0) == -1)
    {
        perror("send");
        exit(1);
    }
    close(sd);
    return 0;
}

// 2 server
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define PORTNUM 9002

int main(void)
{
    char buf[256];
    struct sockaddr_in sin, cli;
    int sd, ns, clientlen = sizeof(cli);

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    memset((char *)&sin, '\0', sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORTNUM);
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(sd, (struct sockaddr *)&sin, sizeof(sin)))
    {
        perror("bind");
        exit(1);
    }
    if (listen(sd, 5))
    {
        perror("listen");
        exit(1);
    }
    while (1)
    {
        if ((ns = accept(sd, (struct sockaddr *)&cli, &clientlen)) == -1)
        {
            perror("accept");
            exit(1);
        }
        switch (fork())
        {
        case 0:
            close(sd);
            strcpy(buf, "Welcome to Server");
            if (send(ns, buf, strlen(buf) + 1, 0) == -1)
            {
                perror("send");
                exit(1);
            }
            if (recv(ns, buf, strlen(buf), 0) == -1)
            {
                perror("recv");
                exit(1);
            }
            printf("** From Client: %s\n", buf);
            sleep(5);
            exit(0);
        }
        close(ns);
    }

    return 0;
}

// 3 server
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PORTNUM 9002
int main(void)
{
    char buf[256];
    struct sockaddr_in sin, cli;
    int sd, ns, clientlen = sizeof(cli);

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    memset((char *)&sin, '\0', sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORTNUM);
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(sd, (struct sockaddr *)&sin, sizeof(sin)))
    {
        perror("bind");
        exit(1);
    }
    if (listen(sd, 5))
    {
        perror("listen");
        exit(1);
    }
    while (1)
    {
        
        if ((ns = accept(sd, (struct sockaddr *)&cli, &clientlen)) == -1)
        {
            perror("accept");
            exit(1);
        }
        printf("** Accept Client\n");

        switch (fork())
        {
        case 0:
            printf("** Fork Client\n");
            close(sd);
            dup2(ns, STDIN_FILENO);
            dup2(ns, STDOUT_FILENO);
            close(ns);
            execl("./han", "han", (char *)0);
        }
        close(ns);
    }

    return 0;
}

// han.c
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    printf("welcom to Server, from han!");
    sleep(5);

    return 0;
}

// 3 client
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define PORTNUM 9002
int main(void)
{
    int sd, len;
    char buf[256];
    struct sockaddr_in sin;

    memset((char *)&sin, '\0', sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORTNUM);
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    printf("==> Create Socket\n");
    if (connect(sd, (struct sockaddr *)&sin, sizeof(sin)))
    {
        perror("connect");
        exit(1);
    }

    printf("==> Connect Server\n");
    if ((len = recv(sd, buf, sizeof(buf), 0)) == -1)
    {
        perror("recv");
        exit(1);
    }
    buf[len] = '\0';
    printf("==> From Server : %s\n", buf);

    close(sd);
    return 0;
}

// 4 serer
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define PORTNUM 9002
int main(void)
{
    char buf[256];
    struct sockaddr_in sin, cli;
    int sd, ns, clientlen = sizeof(cli);

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    memset((char *)&sin, '\0', sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORTNUM);
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(sd, (struct sockaddr *)&sin, sizeof(sin)))
    {
        perror("bind");
        exit(1);
    }
    if (listen(sd, 5))
    {
        perror("listen");
        exit(1);
    }
    while (1)
    {
        if ((ns = accept(sd, (struct sockaddr *)&cli, &clientlen)) == -1)
        {
            perror("accept");
            exit(1);
        }
        printf("** Accept Client\n");

        switch (fork())
        {
        case 0:
            printf("** Fork Client\n");
            close(sd);
            sprintf(buf, "%d", ns);
            execlp("./bit", "bit", buf, (char *)0);
            close(ns);
        }
        close(ns);
    }

    return 0;
}

// bit.c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{
    char buf[256];
    int len, ns;

    ns = atoi(argv[1]);

    strcpy(buf, "Welcome to Server, from Bit");
    if ((send(ns, buf, strlen(buf) + 1, 0)) == -1)
    {
        perror("send");
        exit(1);
    }

    if ((len = recv(ns, buf, strlen(buf), 0)) == -1)
    {
        perror("recv");
        exit(1);
    }
    printf("@@ [Bit] From Client: %s\n", buf);
    close(ns);

    return 0;
}

//4 client
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define PORTNUM 9001
int main(void)
{
    int sd, len;
    char buf[256];
    struct sockaddr_in sin;

    memset((char *)&sin, '\0', sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORTNUM);
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    printf("==> Create Socket\n");
    if (connect(sd, (struct sockaddr *)&sin, sizeof(sin)))
    {
        perror("connect");
        exit(1);
    }

    printf("==> Connect Server\n");
    if ((len = recv(sd, buf, sizeof(buf), 0)) == -1)
    {
        perror("recv");
        exit(1);
    }

    buf[len] = '\0';
    printf("==> From Server : %s\n", buf);

    strcpy(buf, "I want a TELNET Service.");
    if (send(sd, buf, sizeof(buf) + 1, 0) == -1) {
        perror("send");
        exit(1);
    }

    close(sd);
    return 0;
}