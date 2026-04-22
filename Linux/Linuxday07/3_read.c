#include"49func.h"
int main(int argc,char *argv[]){
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR);//返回文件标识符
    ERROR_CHECK(fd,-1,"open");
    char buf[1024];
    ssize_t  ret = read(fd,buf,5);
    printf("buf = %s\n",buf);
    printf("ret = %ld\n",ret);
    close(fd);
    return 0;
}
