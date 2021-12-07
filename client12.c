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
