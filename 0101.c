// ex 1-1
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
/*
연습문제 1-1
유닉스 시스템 프로그래밍이 무엇인지 간략하게 설명하라.

-> 유닉스에서 제공하는 시스템 호출을 이용해서 프로그램을 작성하는 것

연습문제 1-2
시스템 호출과 라이브러리 함수의 동작 과정을 비교하여 설명하라

-> 
시스템 호출 : 직접 커널에 접근하여 해당 모듈을 호출
라이브러리 함수: 함수 내부의 시스템 호출을 이용해 커널에 접근

연습문제 1-3
mkdir은 명령이기도 하지만, 시스템 호출이기도 하다. 명령과 시스템 호출에 해당하는 맨페이지(man)를 보는 방법은 각각 무엇인가?

-> 
명령 : man -s 1 mkdir
시스템 호출 : man -s 2 mkdir

연습문제 1-4
access 함수를 사용한 프로그램을 작성했는데 오류가 발생했다. errno 변수를 출력해보니 13이 출력되었다. 이 13이 어떤 오류인지 확인하는 방법을 설명하라.

-> 
perror(“access”)
명령어를 사용하면 access에 대한 오류메시지가 출력된다.



연습문제 1-5
rmdir 명령으로 temp 디렉토리를 삭제하려고 했는데 디렉토리가 비어 있지 않다는 오류 메시지를 출력했다. 무엇이 문제인가?

-> 
rmdir -r temp
명령어를 사용해 하위 디렉토리까지 삭제할 수 있음.

연습문제 1-6
소스 파일(.c)을 컴파일 해 실행 파일을 생성하는 과정을 설명하라.

-> 
gcc -o 실행파일.out 소스파일.c
명령어를 사용해 실행파일을 생성

연습문제 1-8
프로그램을 실행하는 도중에 정수값 200개를 저장할 수 있는 메모리를 할당하려면 어떻게 해야 하는가?

->
int* numArr;
numArr=(int*)malloc(sizeof(int)*200);
를 사용해 메모리를 할당 할 수 있다.
*/

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

/* vi 명령어 정리
1. command 모드
    i : 현재 커서 위치에 삽입후 입력모드로 전환
    a : 현재 커서 바로 다음위치에 삽입 후 입력모드로 전환
    o : 현재 줄 다음 위치에 삽입 후 입력모드로 전환
    x : 커서가 위치한 곳의 글자 1개 삭제 ( 3x는 3개 삭제)
    dw : 커서가 위치한 곳에서 부터 한 단어 삭제
    dd : 커서가 위치한 곳이 한 줄 복사 후 삭제 (p로 복구 가능, 3dd는 3줄 복사 후 삭제)
    u : 이전 명령 취소
    yy : 현재 줄을 복사 (3yy는 3줄 복사)
    p : 현재 커서가 있는 줄 바로 아래에 복사한 내용 붙여넣기
    k : 커서 위로 이동
    j : 커서 아래로 이동
    l : 커서 한칸 오른쪽으로 이동
    h : 커서 한칸 왼쪽으로 이동
    0: 커서가 있는 줄의 맨 앞으로 이동
    $ : 커서가 있는 줄의 맨 뒤로 이동
    ( : 현재 문장의 처음
    ) : 현재 문장의 끝
    { : 현재 문단의 처음
    } : 현재 문단의 끝
    - : 윗줄로 이동 (3- 는 세줄 위로 이동)
    + : 아랫줄로 이동 (3+ 는 세줄 아래로 이동)
    G : 파일의 끝으로 이동
    r : 한 문자 변경
    cc : 커서가 있는 줄의 내용 변경

2. last line 모드 (esc후 :을 누른 상태)
    w : 현재 파일명으로 저장
    w [파일명] : 해당 파일명으로 저장
    q : 저장하지 않고 종료
    q! : 저장하지 않고 강제종료
    wq : 저장 후 종료
    wq! : 저장 후 강제종료
    f [파일명] : 해당 파일명으로 이름 변경
    [숫자] : 해당 줄로 커서 이동
    $ : 파일의 맨 끝 줄로 커서 이동
    e! : 마지막 저장 이후 모든 편집 취소
    /[문자열] : 현재 커서위치에서부터 파일 앞쪽으로 문자열 탐색
    ?[문자열] : 현재 커서위치에서부터 파일 뒤쪽으로 문자열 탐색
    set nu : vi라인 번호 출력
    set nonu : vi라인 번호 출력 취소
*/

