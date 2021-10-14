//ex 2-1
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
	int fd;
	mode_t mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	
	fd = open("unix.txt", O_CREAT, mode);
	if (fd == -1) {
		perror("Creat");
		exit(1);
	}
	close(fd);
	return 0;
}

//ex 2-2
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main (void) {
	int fd;

	fd = open("unix.txt", O_CREAT | O_EXCL, 0644);
	if (fd == -1) {
		perror("Excl");
		exit(1);
	}
	close(fd);

	return 0;
}

//ex 2-3
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
	int fd;
	
	close(0);

	fd = open("unix.txt", O_RDWR);
	if (fd == -1) {
		perror("Excl");
		exit(1);
	}

	printf("unix.txt : fd = %d\n", fd);
	close(fd);

	return 0;
}


//ex 2-4
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int rfd, wfd, n;
    char buf[10];

    rfd = open("unix.txt", O_RDONLY);
	if (rfd == -1) {
        perror("Open unix.txt");
        exit(1);
    }

    n = read(rfd, buf, 6);
    if (n == -1) {
      perror("Read");
      exit(1);
    }
    
    buf[n] = '\0';
    printf("n = %d, buf = %s\n", n, buf);
    close(rfd);

    return 0;
}

//ex 2-5
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int rfd, wfd, n;
    char buf[10];

    rfd = open("unix.txt", O_RDONLY);
    if (rfd == -1) {
        perror("Open unix.txt");
        exit(1);
    }

    wfd = open("unix.bak", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (wfd == -1) {
        perror("Open unix.bak");
        exit(1);
    }

    while ((n = read(rfd, buf, 6)) > 0)
        if (write(wfd, buf, n) != n)
            perror("Write");

    if (n == -1)
        perror("Read");

    close(rfd);
    close(wfd);

    return 0;
}

//ex 2-6
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int fd, n;
    off_t start, cur;
    char buf[256];

    fd = open("unix.txt", O_RDONLY);
    if (fd == -1) {
        perror("Open unix.txt");
        exit(1);
    }

    start = lseek(fd, 0, SEEK_CUR);
    n = read(fd, buf, 255);
    buf[n] = '\0';
    printf("Offset start=%d, Read Str=%s, n=%d\n", (int)start, buf, n);

    cur = lseek(fd, 0, SEEK_CUR);
    printf("Offset cur=%d\n", (int)cur);

    start = lseek(fd, 5, SEEK_SET);
    n = read(fd, buf, 255);
    buf[n] = '\0';
    printf("Offset start=%d, Read Str=%s", (int)start, buf);

    close(fd);

    return 0;
}

//ex 2-7
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int fd, fd1;

    fd = open("tmp.aaa", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Create tmp.aaa");
        exit(1);
    }

    close(1);

    fd1 = dup(fd);

    printf("DUP FD=%d\n", fd1);
    printf("Standard Output Redirection\n");
    close(fd);

    return 0;
}

//ex 2-8
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int fd;

    fd = open("tmp.bbb", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Create tmp.bbb");
        exit(1);
    }

    dup2(fd, 1);
    printf("DUP2 : Standard Output Redirection\n");

    close(fd);
    
    return 0;
}

//ex 2-9
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int fd, flags;
    fd = open("unix.txt", O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    if ((flags = fcntl(fd, F_GETFL)) == -1) {
        perror("fcntl");
        exit(1);
    }

    flags |= O_APPEND;
    if (fcntl(fd, F_SETFL, flags) == -1) {
        perror("fcntl");
        exit(1);
    }

    if (write(fd, "KOREA Media\n", 12) != 12) perror("write");

    close(fd);

    return 0;
}

//ex 2-10
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int cnt;

    cnt = unlink("tmp.aaa");
    if (cnt == -1) {
        perror("Unlink tmp.aaa");
        exit(1);
    }
    
    printf("Unlink tmp.aaa success!!!\n");

    return 0;
}

//ex 2-11
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    FILE *rfp,*wfp;
    int c;
    if ((rfp = fopen("unix.txt", "r")) == NULL) {
        perror("fopen: unix.txt");
        exit(1);
    }

    if ((wfp = fopen("unix.out", "w")) == NULL) {
        perror("fopen: unix.out");
        exit(1);
    }

    while ((c = fgetc(rfp)) != EOF) {
        fputc(c, wfp);
    }
    fclose(rfp);
    fclose(wfp);
    return 0;
}

//ex 2-12
#include <stdlib.h>
#include <stdio.h>
int main(void) {
    FILE *rfp, *wfp;
    char buf[BUFSIZ];

    if ((rfp = fopen("unix.txt", "r")) == NULL) {
        perror("fopen: unix.txt");
        exit(1);
    }

    if ((wfp = fopen("unix.out", "a")) == NULL) {
        perror("fopen: unix.out");
        exit(1);
    }

    while (fgets(buf, BUFSIZ, rfp) != NULL) {
        fputs(buf, wfp);
    }
    fclose(rfp);
    fclose(wfp);

    return 0;
}

//ex 2-13
#include <stdlib.h>
#include <stdio.h>
int main(void) {
    FILE *rfp;
    char buf[BUFSIZ];
    int n;

    if ((rfp = fopen("unix.txt", "r")) == NULL) {
        perror("fopen: unix.txt");
        exit(1);
    }

    while ((n = fread(buf, sizeof(char) * 2, 3, rfp)) > 0) {
        buf[6] = '\0';
        printf("n=%d, buf=%s\n", n, buf);
    }

    fclose(rfp);

    return 0;
}

//ex 2-14
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    FILE *rfp, *wfp;
    char buf[BUFSIZ];
    int n;

    if ((rfp = fopen("unix.txt", "r")) == NULL) {
        perror("fopen: unix.txt");
        exit(1);
    }

    if ((wfp = fopen("unix.out", "a")) == NULL) {
        perror("fopen: unix.out");
        exit(1);
    }

    while ((n = fread(buf, sizeof(char) * 2, 3, rfp)) > 0) {
        fwrite(buf, sizeof(char) * 2, n, wfp);
    }

    fclose(rfp);
    fclose(wfp);

    return 0;
}

//ex 2-15
#include <stdlib.h>
#include <stdio.h>
int main(void) {
    FILE *rfp;
    int id, s1, s2, s3, s4, n;

    if ((rfp = fopen("unix.dat", "r")) == NULL) {
        perror("fopen: unix.dat");
        exit(1);
    }

    printf("학번 평균\n");
    while ((n = fscanf(rfp, "%d %d %d %d %d", &id, &s1, &s2, &s3, &s4)) != EOF) {
        printf("%d : %d\n", id, (s1 + s2 + s3 + s4) / 4);
    }

    fclose(rfp);

    return 0;
}

//ex 2-16
#include <stdlib.h>
#include <stdio.h>
int main(void) {
    FILE *rfp, *wfp;
    int id, s1, s2, s3, s4, n;

    if ((rfp = fopen("unix.dat", "r")) == NULL) {
        perror("fopen: unix.dat");
        exit(1);
    }

    if ((wfp = fopen("unix.scr", "w")) == NULL) {
        perror("fopen: unix.scr");
        exit(1);
    }

    fprintf(wfp, "학번 평균\n");
    while ((n = fscanf(rfp, "%d %d %d %d %d", &id,&s1,&s2,&s3,&s4)) != EOF) {
        fprintf(wfp, "%d : %d\n", id, (s1 + s2 + s3 + s4) / 4);
    }

    fclose(rfp);
    fclose(wfp);

    return 0;
}

//ex 2-17
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    FILE *fp;
    int n;
    long cur;
    char buf[BUFSIZ];

    if ((fp = fopen("unix.txt", "r")) == NULL) {
        perror("fopen: unix.txt");
        exit(1);
    }

    cur = ftell(fp);
    printf("Offset cur=%d\n", (int)cur);

    n = fread(buf, sizeof(char), 4, fp);
    buf[n] = '\0';
    printf("-- Read Str=%s\n", buf);

    fseek(fp, 1, SEEK_CUR);

    cur = ftell(fp);
    printf("Offset cur=%d\n", (int)cur);

    n = fread(buf, sizeof(char), 6, fp);
    buf[n] = '\0';
    printf("-- Read Str=%s\n", buf);

    cur = 12;
    fsetpos(fp, &cur);

    fgetpos(fp, &cur);
    printf("Offset cur=%d\n", (int)cur);

    n = fread(buf, sizeof(char), 13, fp);
    buf[n] = '\0';
    printf("-- Read Str=%s\n", buf);

    fclose(fp);

    return 0;
}

//ex 2-18
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
int main(void) {
    FILE *fp;
    int fd;
    char str[BUFSIZ];

    fd = open("unix.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    fp = fdopen(fd, "r");

    fgets(str, BUFSIZ, fp);
    printf("Read : %s\n", str);

    fclose(fp);

    return 0;
}

//ex 2-19
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
int main(void) {
    FILE *fp;
    int fd, n;
    char str[BUFSIZ];

    fp = fopen("unix.txt", "r");
    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }

    fd = fileno(fp);
    printf("fd : %d\n", fd);

    n = read(fd, str, BUFSIZ);
    str[n] = '\0';
    printf("Read : %s\n", str);

    close(fd);

    return 0;
}

//ex 2-20
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *fname;
    char fntmp[BUFSIZ];
    char template[32];

    fname = tmpnam(NULL);
    printf("1. TMP File Name(tmpnam) : %s\n", fname);

    tmpnam(fntmp);
    printf("2. TMP File Name(tmpnam) : %s\n", fntmp);

    fname = tempnam("/tmp", "linux");
    printf("3. TMP File Name(tempnam) : %s\n", fname);

    strcpy(template, "/tmp/linuxXXXXXX");
    fname = mktemp(template);
    printf("4. TMP File Name(mktemp) : %s\n", fname);

    return 0;
}

//prac 2-1
//저수준 파일 입출력을 이용해 mycat프로그램을 작성하라. 출력시 행 번호를 붙여서 출력 한다.
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int hang = 1, i = 0, n = 0;
    int fd;
    char buf[256];

    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    printf("%d행: ", hang++);

    while ((n = read(fd, buf, 256)) > 0) {
        for (i = 0; i < n; i++) {
            printf("%c", buf[i]);
            if (buf[i] == '\n') {
                printf("\n%d행: ", hang++);
            }
        }
    }

    printf("\n");
    close(fd);
    return 0;
}

//prac 2-2
//저수준 파일 입출력을 이용해 파일을 복사하는 프로그램을 작성하라. 파일명은 명령행 인자로 받는다.
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int fd1, fd2, n;
    char buf[256];

    fd1 = open(argv[1], O_RDONLY);
    if(fd1 == -1) {
        perror("First Parameter");
        exit(1);
    }

    fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd2 == -1) {
        perror("Secon Parameter");
        exit(1);
    }

    while ((n = read(fd1, buf, 256)) > 0)
        write(fd2, buf, n);

    close(fd1);
    close(fd2);
    return 0;
}

//prac 2-3
//lseek함수를 사용해 데이터 파일을 읽고 아래 출력 형태와 같이 출력하는 프로그램을 작성하시오
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
    int fd1, fd2, n;
    char ch;

    fd1 = open("in.txt", O_RDONLY);
    if(fd1 == -1) {
        perror("Read");
        exit(1);
    }

    fd2 = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if(fd2 == -1){
        perror("open");
        exit(1);
    }

    while ((n = read(fd1, &ch, 1)) > 0) {
        write(fd2, &ch, n);
        lseek(fd1, 1, SEEK_CUR);
    }

    close(fd1);
    close(fd2);

    return 0;
}

//prac 2-4
//연습문제 3번을 fread와 fwrite 함수를 사용해 동일한 결과를 출력하도록 작성하라.
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    FILE *fp1, *fp2;
    int n;
    char ch;

    fp1 = fopen("in", "r");
    fp2 = fopen("out", "w+");

    while ((n = fread(&ch, sizeof(char), 1, fp1)) > 0) {
        fwrite(&ch, sizeof(char), 1, fp2);
        fseek(fp1, 1, SEEK_CUR);
    }

    return 0;
}

//prac 2-5
//고수준 파일 입출력을 이용해 파일명을 변경하는 프로그램을 작성하라. 파일명은 명령행으로 받는다.
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *fp1, *fp2;
    int n;
    char buf[256];

    fp1 = fopen(argv[1], "r");
    fp2 = fopen(argv[2], "w+");

    while ((n = fread(buf, sizeof(char), 256, fp1)) > 0)
        fwrite(buf, sizeof(char), n, fp2);
    unlink(argv[1]);

    fclose(fp1);
    fclose(fp2);

    return 0;
}

//prac 2-6
//다음 데이터 파일을 읽어 학번과 평균을 출력하는 프로그램을 작성하라.
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd, n = 1, i = 0, k = 0;
    char buf[10];
    int g[4];
    char ch;

    fd = open("./grade.txt", O_RDONLY);
    while (1) {
        n = read(fd, &ch, 1);
        if (n <= 0)
            break;
        if (ch == ' ' || ch == '\n') {
            buf[k] = '\0';
            g[i++] = atoi(buf);
            k = 0;

            if (ch == '\n') {
                printf("ID: %d / AVG: %d\n", g[0], (g[1] + g[2] + g[3]) / 3);
                i = 0;
            }
        }
        else {
            buf[k++] = ch;
        }
    }

    return 0;
}

//prac 2-7
//임시 파일을 생성해 파일명을 출력하고, 이 파일에 학번과 이름을 출력하는 프로그램을 작성하라.
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    FILE *fp;
    char buf[20];
    char *fname;

    fname = tempnam("./", "tmp");
    fp = fopen(fname, "w+");

    printf("temp file name : %s \n", fname);
    fprintf(fp, "%d %s", 201712605, "JeongWonJoon");

    fclose(fp);

    return 0;
}