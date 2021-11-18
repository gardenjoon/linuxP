// // ex 1-1
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

extern int errno;
int main(void)
{
    if (access("unix.txt", F_OK) == -1)
    {
        printf("errno=%d\n", errno);
    }

    return 0;
}

// ex 1-2
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
extern int errno;

int main(void)
{
    FILE *fp;

    if ((fp = fopen("unix.txt", "r")) == NULL)
    {
        printf("errno=%d\n", errno);
        exit(1);
    }
    fclose(fp);

    return 0;
}

// ex 1-3
#include <stdio.h>
extern int addnum(int a, int b);

int main(void)
{
    int sum;

    sum = addnum(1, 5);
    printf("Sum 1~5 = %d\n", sum);

    return 0;
}

// ex 1-3.addnum
int addnum(int a, int b)
{
    int sum = 0;

    for (; a <= b; a++)
        sum += a;
    return sum;
}

// ex1-3 Makefile
/*
# Makefile

CC = gcc
CFLAGS =
OBJS = ex1_3_main.o ex1_3_addnum.o
LIBS =
all:	add
add: 	$(OBJS)
    $(CC) $(CFLAGS) -o add $(OBJS) $(LIBS)

ex1_3_main.o:		ex1_3_main.c
    $(CC) $(CFLAGS) -c ex1_3_main.c
ex1_3_addnum.o: 		ex1_3_addnum.c
    $(CC) $(CFLAGS) -c ex1_3_addnum.c

clean:
    rm -f $(OBJS) add core
*/

// ex 1-4
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    if (access("unix.txt", R_OK) == -1)
    {
        perror("unix.txt");
        exit(1);
    }

    return 0;
}

//ex 1-5
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern int errno;

int main(void) {
	char *err;

	if (access("unix.txt", R_OK) == -1) {
		err = strerror(errno);
		printf("오류:%s(unix.txt)\n", err);
		exit(1);
	}

	return 0;
}

//ex1-6
#include <stdio.h>

int main(int argc, char *argv[]) {
	int n;

	printf("argc = %d\n", argc);
	for (n = 0; n < argc; n++)
		printf("argv[%d] = %s\n", n, argv[n]);

	return 0;
}

//ex1-7
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int n;
	extern char *optarg;
	extern int optind;

	printf("Current Optind : %d\n", optind);
	while ((n = getopt(argc, argv, "abc:")) != -1) {
		switch (n) {
			case 'a':
				printf("Option : a\n");
				break;
			case 'b':
				printf("Option : b\n");
				break;
			case 'c':
				printf("Option : c, Argument=%s\n", optarg);
				break;
		}
		printf("Next Optind : %d\n", optind);
	}
	
	return 0;
}


// prac 1-9 명령행 인자와 getopt함수를 사용해 다음 명령을 처리하는 프로그램을 작성하라.
#include <stdio.h>
 
int main(int argc, char argv[]){
   int n;
 
   extern char* optarg;
 
   if(argc==1)
       printf("You can use option a, u, h \n");
 
   while((n=getopt(argc, argv, "au:h"))!=-1){
       switch(n){
           case 'a':
               printf("Welcome to Unix System Programming World!!!\n");
               break;
           case 'u':
               printf("Nice to meet %s \n", optarg);
               break;
           case 'h':
               printf("You can use option a, u, h \n");
               break;
       }
   }
 
   return 0;
}





# Makefile

CC = gcc
CFLAGS=
OBJS = exam_main.o exam_addnum.o
LIBS=
all:    add

add:    $(OBJS)
    $(CC) $(CFLAGS) -o add $(OBJS) $(LIBS)

exam_main.o:         exam_main.c
    $(CC) $(CFLAGS) -c exam_main.c

exam_addnum.o:       exam_addnum.c
    $(CC) $(CFLAGS) -c exam_addnum.c
clean:
  rm -f $(OBJS) add core