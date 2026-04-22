#include"49func.h"
int main(){
    int fd_out = dup(STDOUT_FILENO);//保存标准输出，实际上是fd_out指向标准输出
    printf("1. hello world.\n");
    int fdw = open("1.pipe",O_WRONLY);
    ERROR_CHECK(fdw,-1,"open");
    //printf("1. hello world.\n");
    dup2(fdw,STDOUT_FILENO);
    printf("2. hello world");
    dup2(fd_out,STDOUT_FILENO);
    printf("3. hello world.\n");
    close(fdw);
    return 0;
}
