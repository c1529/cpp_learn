#include"49func.h"
int main(int argc,char* argv[]){
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR);
    int ret = ftruncate(fd,4096000);// 对于小的文件会造成文件空洞，常常用于多任务下载对于磁盘空间的占用
    ERROR_CHECK(ret,-1,"ftruncate");
    close(fd);
    return 0;
}
