#include"49func.h"
int main(int argc,char* argv[]){
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    write(fd,"hello",5);
    lseek(fd,-1,SEEK_CUR);
    write(fd,"O",1);
    close(fd);
    return 0;
}

