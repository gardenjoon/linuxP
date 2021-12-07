#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <stdio.h>

#define SOCKET_NAME "prac"

int main(void)
{
    char buf[256];
    struct sockaddr_un ser, cli;
    int sd, nsd, len, clen;
    FILE* fs;
    char str[256];

    if ((sd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    unlink(SOCKET_NAME);

    memset((char *)&ser, '\0', sizeof(ser));
    ser.sun_family = AF_UNIX;
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
    
    clen = sizeof(cli);
    if ((nsd = accept(sd, (struct sockaddr *)&cli, &clen)) == -1)
    {
        perror("accept");
        exit(1);
    }
    if (recv(nsd, buf, sizeof(buf), 0) == -1)
    {
        perror("recv");
        exit(1);
    }

    fs = fopen(buf, "r");
    fgets(str, 256, fs);
    printf("%s\n", str);

    close(nsd);
    close(sd);

    return 0;
}