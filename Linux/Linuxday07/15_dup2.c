#include"49func.h"
int main(int argc,char *argv[]){
    // ./15_dup2 file
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    printf("我过来了\n");
    int new_fd =10;

    dup2(STDOUT_FILENO,new_fd);   // 让new_fd 指向和STDOUT_FILENO同一个文件
    dup2(fd,STDOUT_FILENO);
    printf("我过去了\n");
    dup2(new_fd,STDOUT_FILENO);
    printf("我又过来了\n");
    close(fd);
    return 0;
}
