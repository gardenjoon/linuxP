#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    DIR *dp;
    struct dirent *dent;

    dp = opendir(".");

    while ((dent = readdir(dp)) != NULL) {
        if (dent->d_name[0] == '.')
            continue;

        DIR *file;

        if ((file = opendir(dent->d_name)) == NULL) {
            printf("File : %s\n", dent->d_name);
        }

        else {
            printf("DIR : %s\n", dent->d_name);
        }
    }

    return 0;
}