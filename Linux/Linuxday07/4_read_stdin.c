#include"49func.h"
int main(){
    int fd = 0;//文件描述符0在表示LINUX系统里面表示stdin 1:stdout 2:stderr
    char buf[1024]={0};
    ssize_t ret = read(0,buf,sizeof(buf));
    ERROR_CHECK(ret,-1,"read");
    printf("buf = %s    ret = %ld\n",buf,ret);// 有换行符\n 所以ret实际上是+1
    return 0;
}



