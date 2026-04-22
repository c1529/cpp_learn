#include"49func.h"
int main(int argc,char* argv[]){
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    int data = 100000;
    ssize_t ret = write(fd,&data,sizeof(data));// 写入二进制数据
    ERROR_CHECK(ret,-1,"write");
    printf("ret = %ld\n",ret);
    close(fd);
    return 0;
}
