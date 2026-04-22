#include"49func.h"
int main(int argc,char* argv[]){
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR|O_CREAT|O_TRUNC,0666);
    ERROR_CHECK(fd,-1,"open");
    char buf[100000];
    for(int i=0;i<100000;i++){
        buf[i]='1';
    }
    for(int i=0;i<10;i++){
        write(fd,buf,100000);
    }
    close(fd);
    return 0;
}
