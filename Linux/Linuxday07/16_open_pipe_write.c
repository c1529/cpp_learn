#include"49func.h"
int main(int argc,char* argv[]){
    ARGS_CHECK(argc,2);
    int fd_write = open(argv[1],O_WRONLY);
    ERROR_CHECK(fd_write,-1,"open");
    printf("write side is opened.\n");
    close(fd_write);
    return 0;
}
