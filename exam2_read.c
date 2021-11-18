#include <stdlib.h>
#include <stdio.h>

int main(void) {
    FILE *rfp;
    FILE *wfp;
    char name[100];
    int korean, english, math, n, i;
    int studentNumber = 5;

    if((rfp = fopen("scores.txt", "r")) == NULL) {
        perror("fopen: scores.txt");
        exit(1);
    }

    while((n=fscanf(rfp, "%s %d %d %d", name, &korean, &english, &math)) != EOF) {
        printf("이름 : %s, 합계 : %d, 평균 : %d\n ", name, english + math + korean, (english+math+korean) / 3);
    }

    if((wfp = fopen("lastScores.txt", "a")) == NULL) {
        perror("fopen: lastScores.txt");
        exit(1);
    }

    for (int i = 0; i < studentNumber-1; i++) {
        fprintf(wfp, "%s %d %d %d\n", name, korean ,english, math);
    }

    fclose(rfp);
    fclose(wfp);

    return 0;
}