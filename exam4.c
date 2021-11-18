#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int opt;

    if (argc < 2) {
        perror("argument needed");
        exit(1);
    }

    while ((opt = getopt(argc, argv, "ay")) != -1) {
        switch(opt) {
            case 'a':
                printf("%d-%d-%d %d:%d:%d\n", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
                break;
            case 'y':
                printf("%d\n", tm.tm_year+1900);
                break;
        }
    }

  return 0;
}