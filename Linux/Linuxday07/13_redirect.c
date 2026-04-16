#include"49func.h"
// 重定向  printf()默认输出到1里面，把1(stdout)关闭，然后重新打开一个文件，该文件fd是1,导致printf输出到文件中
int main(int argc,char *argv[]){
    // ./13_redirect file
    ARGS_CHECK(argc,2);
    printf("you can see me.\n");
    close(STDOUT_FILENO); //STDOUT_FILENO 是 1
    int fd = open(argv[1],O_RDWR);
    printf("file fd is %d.\n",fd);
    printf("hello world.\n");
    printf("you can't see me.\n");
    return 0;
}
