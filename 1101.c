#include <netdb.h>
#include <stdio.h>

int main(void)
{
    struct hostent *hent;

    sethostent(0);
    while ((hent = gethostent()) != NULL)
        printf("Name=%s\n", hent->h_name);
    endhostent();

    return 0;
}

// 2
#include <netdb.h>
#include <stdio.h>

int main(void)
{

    struct servent *port;
    int n;
    setservent(0);
    for (n = 0; n < 5; n++)
    {
        port = getservent();
        printf("Name=%s, Port=%d\n", port->s_name, port->s_port);
    }
    endservent();

    return 0;
}

// 3
#include <netdb.h>
#include <stdio.h>

int main(void)
{
    struct servent *port;
    int n;
    setservent(0);
    for (n = 0; n < 5; n++)
    {
        port = getservent();
        printf("Name=%s, Port=%d\n", port->s_name, ntohs(port->s_port));
    }
    endservent();

    return 0;
}

// 4
#include <netdb.h>
#include <stdio.h>

int main(void)
{
    struct servent *port;
    port = getservbyname("telnet", "tcp");
    printf("Name=%s, Port=%d\n", port->s_name, ntohs(port->s_port));

    port = getservbyport(htons(21), "tcp");
    printf("Name=%s, Port=%d\n", port->s_name, ntohs(port->s_port));

    return 0;
}

// 5
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>

int main(void)
{
    in_addr_t addr;
    struct hostent *hp;
    struct in_addr in;

    if ((addr = inet_addr("218.237.65.4")) == (in_addr_t)-1)
    {
        printf("Error : inet_addr(203.250.126.211\n");
        exit(1);
    }

    hp = gethostbyaddr((char *)&addr, 4, AF_INET);
    if (hp == NULL)
    {
        (void)printf("Host information not found\n");
        exit(2);
    }

    printf("Name=%s\n", hp->h_name);

    (void) memcpy(&in.s_addr, *hp->h_addr_list, sizeof(in.s_addr));
    printf("IP=%s\n", inet_ntoa(in));
    return 0;
}

// 6
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/un.h>

#define SOCKET_NAME "LSPsocket"

int main(void)
{
    char buf[256];
    struct sockaddr_un ser, cli;
    int sd, nsd, len, clen;

    if ((sd = socekt(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    memset((char *)&ser, 0, sizeof(struct sockaddr_un));
    ser.sun_family = AF_INET;
    strcpy(ser.sun_path, SOCKET_NAME);
    len = sizeof(ser.sun_family) + strlen(ser.sun_path);

    if (bind(sd, (struct sockaddr *)&ser, len))
    {
        perror("bind");
        exit(1);
    }

    if (listen(sd, 5) < 0)
    {
        perror("listen");
        exit(1);
    }

    printf("Wating ...\n");
    if ((nsd = accept(sd, (struct sockaddr *)&cli, &clen)) == -1)
    {
        perror("accept");
        exit(1);

        if (recv(nsd, buf, sizeof(buf), 0) == -1)
        {
            perror("recv");
            exit(1);
        }
    }

    pritnf("Received Message: %s\n", buf);
    close(nsd);
    close(sd);

    return 0;
}

// 6-2
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/un.h>

#define SOCKET_NAME "LSPocket"

int main(void)
{
    int sd, len;
    char buf[256];
    struct sockaddr_un ser;

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    memset((char *)&ser, '\0', sizeof(ser));
    ser.sun_family = AF_INET;
    strcpy(ser.sun_path, SOCKET_NAME);
    len = sizeof(ser.sun_family) + strlen(ser.sun_path);

    if (connect(sd, (struct sockaddr *)&ser, len) < 0)
    {
        perror("bind");
        exit(1);
    }

    strcpy(buf, "Unix Domain Socket Test Message");
    if (send(sd, buf, sizeof(buf), 0) == -1)
    {
        perror("send");
        exit(1);
    }
    close(sd);

    return 0;
}

// 7
#define PORTNUM 9000

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
    sin.sin_addr.s_addr = inet_addr("192.168.162.133");

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

    if ((ns = accept(sd, (struct sockaddr *)&cli, &clientlen)) == -1)
    {
        perror("accept");
        exit(1);
    }
    sprintf(buf, "Your IP address is %s", inet_ntoa(cli.sin_addr));
    if (send(ns, buf, strlen(buf) + 1, 0) == -1)
    {
        perror("send");
        exit(1);
    }
    close(ns);
    close(sd);

    return 0;
}

// 7-2

#define PORTNUM 9000

int main(void)
{
    int sd;
    char buf[256];
    struct sockaddr_in sin;
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    memset((char *)&sin, '\0', sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORTNUM);
    sin.sin_addr.s_addr = inet_addr("192.168.162.133");

    if (connect(sd, (struct sockaddr *)&sin, sizeof(sin))) {
        perror("connect");
        exit(1);
    }

    if (recv(sd, buf, sizeof(buf), 0) == -1) {
        perror("recv");
        exit(1);
    }

    close(sd);
    printf("From server : %s\n", buf);

    return 0;
}
