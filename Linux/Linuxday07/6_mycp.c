#include"49func.h"
int main(int argc,char* argv[]){
    // ./6_mycp src dest
    ARGS_CHECK(argc,3);
    int fd_src = open(argv[1],O_RDONLY);
    int fd_dest = open(argv[2],O_RDWR | O_CREAT |O_TRUNC,0777);
    char buf[16];
    // 读取文件内容
    ssize_t ret_read;
    //循环读取
    long total = 0;
    while((ret_read = read(fd_src,buf,sizeof(buf)))>0){
        ssize_t ret_write = write(fd_dest,buf,ret_read);
        total++;
    }
    close(fd_src);
    close(fd_dest);
    printf("一共复制次数是:total = %ld\n",total);
    return 0;
}
