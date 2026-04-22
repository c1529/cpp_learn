#include"49func.h"
int main(int argc,char *argv[]){
// ./2_write file_path
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    char buf[]="hello world";
    long ret = write(fd,buf,strlen(buf));
    printf("buf strlength = %zu\n",strlen(buf));
    printf("ret = %ld\n",ret);
    close(fd);
    return 0;
}
