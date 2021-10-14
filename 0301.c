//ex 3-1
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(void) {
    struct stat buf;
    stat("unix.txt", &buf);
    printf("Inode = %d\n", (int)buf.st_ino);
    printf("Mode = %o\n", (unsigned int)buf.st_mode);
    printf("Nlink = %o\n", (unsigned int)buf.st_nlink);
    printf("UID = %d\n", (int)buf.st_uid);
    printf("GID = %d\n", (int)buf.st_gid);
    printf("SIZE = %d\n", (int)buf.st_size);
    printf("Atime = %d\n", (int)buf.st_atime);
    printf("Mtime = %d\n", (int)buf.st_mtime);
    printf("Ctime = %d\n", (int)buf.st_ctime);
    printf("Blksize = %d\n", (int)buf.st_blksize);
    printf("Blocks = %d\n", (int)buf.st_blocks);
    // printf("FStype = %s\n", buf.st_fstype);
    return 0;
}

//ex 3-2
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int fd;
    struct stat buf;
    fd = open("unix.txt", O_RDONLY);
    if (fd = -1)
    {
        perror("open: unix.txt");
        exit(1);
    }
    fstat(fd, &buf);

    printf("Inode = %d\n", (int)buf.st_ino);
    printf("UID = %s\n", buf.st_uid);
    close(fd);

    return(0);
}

//ex 3-3
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(void) {
    struct stat buf;
    int kind;

    stat("unix.txt", &buf);
    printf("Mode = %o (16진수: %x)\n", (unsigned int)buf.st_mode, (unsigned int)buf.st_mode);

    kind = buf.st_mode & S_IFMT;
    printf("Kind = %x\n", kind);

    switch (kind) {
        case S_IFIFO:
            printf("unix.txt : FIFO\n");
            break;
        case S_IFDIR:
            printf("unix.txt : Directory\n");
            break;
        case S_IFREG:
            printf("unix.txt : Regular File\n");
            break;
    }

    return 0;
}

//ex 3-4
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(void) {
    struct stat buf;

    stat("unix.txt", &buf);
    printf("Mode = %o (16 진 수 : %x)\n", (unsigned int)buf.st_mode, (unsigned int)buf.st_mode);

    if (S_ISFIFO(buf.st_mode))
        printf("unix.txt : FIFO\n");
    if (S_ISDIR(buf.st_mode))
        printf("unix.txt : Directory\n");
    if (S_ISREG(buf.st_mode))
        printf("unix.txt : Regualr File\n");

    return 0;
}

//ex 3-5
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(void) {
    struct stat buf;

    stat("unix.txt", &buf);
    printf("Mode = %o (16진수: %x)\n", (unsigned int)buf.st_mode, (unsigned int)buf.st_mode);

    if ((buf.st_mode & S_IREAD) != 0)
        printf("unix.txt : user has a read permission\n");
    if ((buf.st_mode & (S_IREAD >> 3)) != 0)
        printf("unix.txt : group has a read permission\n");
    if ((buf.st_mode & S_IROTH) != 0)
        printf("unix.txt : other have a read permission\n");

    return 0;
}

//ex 3-6
#include <sys/errno.h>
#include <unistd.h>
#include <stdio.h>

extern int errno;

int main(void) {
    int per;

    if (access("unix.bak", F_OK) == -1 && errno == ENOENT)
        printf("unix.bak: File not exist.\n");

    per = access("unix.txt", R_OK);
    if (per == 0)
        printf("unix.txt: Read permission is permitted.\n");
    else if (per == -1 && errno == EACCES)
        printf("unix.txt: Read permission is not permitted.\n");

    return 0;
}

//ex 3-7
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(void) {
    struct stat buf;

    chmod("unix.txt", S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH);
    stat("unix.txt", &buf);
    printf("1.Mode = %o\n", (unsigned int)buf.st_mode);

    buf.st_mode |= S_IWGRP;
    buf.st_mode &= ~(S_IROTH);
    chmod("unix.txt", buf.st_mode);
    stat("unix.txt", &buf);
    printf("2.Mode = %o\n", (unsigned int)buf.st_mode);

    return 0;
}

//ex 3-8
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main(void) {
    struct stat buf;
    stat("unix.txt", &buf);

    printf("Before Link Count = %d\n", (int)buf.st_nlink);
    link("unix.txt", "unix.ln");

    stat("unix.txt", &buf);
    printf("After Link Count = %d\n", (int)buf.st_nlink);
    
    return 0;
}

//ex 3-9
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    symlink("unix.txt", "unix.sym");
    return 0;
}

//ex 3-10
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    struct stat buf;
    printf("1. stat : unix.txt ---\n");

    stat("unix.txt", &buf);
    printf("unix.txt : Link Count = %d\n", (int)buf.st_nlink);
    printf("unix.txt : Inode = %d\n", (int)buf.st_ino);
    printf("2. stat : unix.sym ---\n");

    stat("unix.sym", &buf);
    printf("unix.sym : Link Count = %d\n", (int)buf.st_nlink);
    printf("unix.sym : Inode = %d\n", (int)buf.st_ino);
    printf("3. lstat : unix.sym ---\n");

    lstat("unix.sym", &buf);
    printf("unix.sym : Link Count = %d\n", (int)buf.st_nlink);
    printf("unix.sym : Inode = %d\n", (int)buf.st_ino);

    return 0;
}

//ex 3-11
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    char buf[BUFSIZ];
    int n;

    n = readlink("unix.sym", buf, BUFSIZ);
    if (n == -1)
    {
        perror("readlink");
        exit(1);
    }

    buf[n] = '\0';
    printf("unix.sym : READLINK = %s\n", buf);
    
    return 0;
}

//ex 3-12
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(void) {
    char buf[BUFSIZ];

    realpath("unix.sym", buf);
    printf("unix.sym : REALPATH = %s\n", buf);
    
    return 0;
}

//ex 3-13
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    if (mkdir("han", 0755) == -1) {
        perror("han");
        exit(1);
    }

    if (mkdir("bit", 0755) == -1) {
        perror("bit");
        exit(1);
    }

    if (rename("han", "hanbit") == -1) {
        perror("hanbit");
        exit(1);
    }

    if (rmdir("bit") == -1) {
        perror("bit");
        exit(1);
    }

    return 0;
}

//ex 3-14
#include <stdio.h>
#include <unistd.h>

int main(void) {
    char *cwd;
    char wd[BUFSIZ];
    
    cwd = getcwd(NULL, BUFSIZ);
    printf("1.Current Directory : %s\n", cwd);
    
    chdir("LSP");
    
    getcwd(wd, BUFSIZ);
    printf("2.Current Directory : %s\n", wd);
    
    return 0;
}

//ex 3-15
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    DIR *dp;
    struct dirent *dent;
    
    if ((dp = opendir("LSP")) == NULL) {
        perror("opendir: LSP");
        exit(1);
    }
    
    while ((dent = readdir(dp))) {
        printf("Name : %s ", dent->d_name);
        printf("Inode : %d\n", (int)dent->d_ino);
    }

    closedir(dp);

    return 0;
}

//ex 3-16
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void) {
    DIR *dp;
    struct dirent *dent;
    struct stat sbuf;
    char path[BUFSIZ];

    if ((dp = opendir("LSP")) == NULL) {
        perror("opendir: LSP");
        exit(1);
    }
    
    while ((dent = readdir(dp))) {
        if (dent->d_name[0] == '.') continue;
        else break;
    }
    sprintf(path, "LSP / %s", dent->d_name);
    stat(path, &sbuf);
    
    printf("Name : %s\n", dent->d_name);
    printf("Inode(dirent) : %d\n", (int)dent->d_ino);
    printf("Inode(stat) : %d\n", (int)sbuf.st_ino);
    printf("Mode : %o\n", (unsigned int)sbuf.st_mode);
    printf("Uid : %d\n", (int)sbuf.st_uid);
    
    closedir(dp);
    
    return 0;
}

//ex 3-17
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(void) {
    DIR *dp;
    struct dirent *dent;
    
    if ((dp = opendir("LSP")) == NULL) {
        perror("opendir");
        exit(1);
    }

    printf("**Dir content\n");
    printf("\t --> Start Offset : %ld\n", telldir(dp));

    while ((dent = readdir(dp))) {
        printf("Read : %s ", dent->d_name);
        printf("\t --> Cur Offset : %ld\n", telldir(dp));
    }

    printf("**Dir Pointer Rewind\n");
    rewinddir(dp);

    printf("\t --> Cur Offset : %ld\n", telldir(dp));
    printf("**Move Directory Pointer\n");
    seekdir(dp, 24);
    printf("\t --> Cur Offset : %ld\n", telldir(dp));

    dent = readdir(dp);
    printf("Read %s ", dent->d_name);
    printf("\t --> Next Offset : %ld\n", telldir(dp));

    closedir(dp);
    return (0);
}

//prac 3-1
//파일의 정보를 추출하는 프로그램을 작성하라. 정보를 알고 싶은 파일의 이름은 명령행 인자로 받는다.
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    struct stat buf;
     int access(const char *path, int amode);
    if (stat(argv[1], &buf) == -1) {
		perror("stat");
		return 1;
	};

    printf("File name: %s\n",argv[1]);
    printf("Inode number: %d\n", (int)buf.st_ino);
    printf("File type: "); 

    switch (buf.st_mode & S_IFMT) { 
        case S_IFBLK: printf("block device\n"); break; 
        case S_IFCHR: printf("character device\n"); break; 
        case S_IFDIR: printf("directory\n"); break; 
        case S_IFIFO: printf("FIFO/pipe\n"); break;
        case S_IFLNK: printf("symlink\n"); break; 
        case S_IFREG: printf("regular file\n"); break;
        case S_IFSOCK: printf("socket\n"); break;
        default: printf("unknown?\n"); break;
    }

    printf("access: ");

    if ((buf.st_mode & S_IRUSR) != 0) printf("r"); 
    else 
        printf("-");
    if ((buf.st_mode & S_IWUSR) != 0) printf("w"); 
    else 
        printf("-");
    if ((buf.st_mode & S_IXUSR) != 0) printf("x"); 
    else 
        printf("-");
    if ((buf.st_mode & S_IRGRP) != 0) printf("r"); 
    else 
        printf("-");
    if ((buf.st_mode & S_IWGRP) != 0) printf("w"); 
    else 
        printf("-");
    if ((buf.st_mode & S_IXGRP) != 0) printf("x"); 
    else 
        printf("-");
    if ((buf.st_mode & S_IROTH) != 0) printf("r"); 
    else 
        printf("-");
    if ((buf.st_mode & S_IWOTH) != 0) printf("w"); 
    else 
        printf("-");
    if ((buf.st_mode & S_IXOTH) != 0) printf("x\n"); 
    else 
        printf("-\n");

    printf("UID = %d\n", (int)buf.st_uid);
    printf("Modified Time = %d\n", (int)buf.st_mtime);

    return 0;
}

//prac 3-2
//입력받은 파일의 접근 권한을 출력학고, 접근 권한을 변경하는 프로그램을 작성하라. 문자 모드 기능을 구현한다.
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    char mode;
    int code = 0;
    scanf(argv[2], &mode);

    if(mode == "u+x")
        code += 100;
    else if (mode == "u-x")
        code -= 100;
    else if (mode == "+x")
        code += 111;
    else if (mode == "o-rw")
        code -= 6;
    else if (mode == "g-w")
        code -= 40;
    else if (mode == "g+w")
        code += 40;

    char t_code = '0' + code;
    if (chmod(argv[1], t_code) != 0) {
        perror("failed change mode\n");
        return 1;
    }
    else {
        printf("success change mode\n");
        return 0;
    }
}

//prac 3-3
//입력받은 파일의 접근 권한을 출력하고, 접근 권한을 변경하는 프로그램을 작성하라. 숫자 모드 기능을 구현한다.
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc,char **argv) {
    int mode = 0;
    sscanf(argv[2], "0%o",&mode);

    if(chmod(argv[1],mode)!=0) {
        printf("failed change mode\n");
    }
    else {
        printf("success change mode\n");
    }
    return 0;
}

//prac 3-4
//디렉토리가 비어 있는지 확인한 후 메시지를 출력하고, 작업 디렉토리를 새로 생성한 디렉토리로 이동시키는 프로그램을 작성하라.
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    int n = 0;
    DIR *dp = opendir("test1");
    struct dirent *dent;

    if (dp == NULL) {
        perror("opendir: test1");
        exit(1);
    }

    while ((dent = readdir(dp)) != NULL) {
        if(++n > 2)
            break;
    }

    closedir(dp);

    if (n <= 2) {
        printf("test1 is empty\n");

        if (rmdir("test1") == -1) {
            perror("rmdir: test1");
            exit(1);
        }
    }

    return 0;
}

//prac 3-5
//디렉토리명을 명령행 인자로 입력받아 디렉토리를 생성하고, 작업 디렉토리를 새로 생성한 디렉토리로 이동시키는 프로그램을 작성하라.
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *curdir;
    char wd[BUFSIZ];

    curdir = getcwd(NULL, BUFSIZ);
    printf("1. Current Directory: %s\n", curdir);

    if (mkdir(argv[1], 0755) == -1) {
        perror("make directory failed");
        exit(1);
    }

    if (chdir(argv[1]) == -1) {
        perror("change directory failed");
        exit(1);
    }

    getcwd(wd, BUFSIZ);
    printf("2. Current Directory : %s\n", wd);

    return 0;
}

//prac 3-6
//.과 .. 항목을 제외한 디렉토리의 모든 내용을 출력하는 myls 프로그램을 작성하라.
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    char *curdir = getcwd(NULL, BUFSIZ);
    DIR *dp;
    struct dirent *dent;

    if ((dp = opendir(curdir)) == NULL) {
        perror("opendir");
        exit(1);
    }

    while ((dent = readdir(dp)) != NULL) {
        if (dent->d_name[0] == '.')
            continue;
        else
            printf("%s\n", dent->d_name);
    }
    closedir(dp);

    return 0;
}

//prac 3-7
//현재 디렉토리의 파일을 지정한 디렉토리로 이동시키는 프로그램을 작성하라.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    char *fileName = argv[1];
    char *dirName = argv[2];
    FILE *srcfile, *destfile;
    char buf[2] = {0};
    int n;
    DIR *dp;

    if ((srcfile = fopen(fileName, "rb")) == NULL) {
        perror("fopen");
        exit(1);
    }
    remove(fileName);

    dp = opendir(dirName);
    chdir(dirName);
    if ((destfile = fopen(fileName, "wb")) == NULL) {
        perror("fopen");
        exit(1);
    }

    while (1) {
        fread(buf,2,1,srcfile);
        
        if (feof(srcfile) != 0) 
            break;
        else 
            fwrite(buf, 2, 1, destfile);
    }

    fclose(srcfile);
    fclose(destfile);
    closedir(dp);

    return 0;
}

//prac 3-8
//현재 디렉토리에 있는 내용을 파일인지 디렉토리인지 구별해 출력하는 프로그램을 작성하라.
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