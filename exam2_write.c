#include <stdlib.h>
#include <stdio.h>

int main(void) {
    FILE *wfp;
    char name[100];
    int korean, english, math, n;
    int studentNumber = 5;

    if ((wfp = fopen("scores.txt", "a")) == NULL) {
        perror("fopen: scores.text");
        exit(1);
    }

    for(int i = 0; i < studentNumber-1; i++){
        scanf("%s %d %d %d\n", name, &korean ,&english , &math);
        fprintf(wfp, "%s %d %d %d\n", name, korean ,english , math);
    }

    fclose(wfp);

    return 0;
}