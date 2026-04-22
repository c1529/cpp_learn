#include"49func.h"
int main(int argc,char* argv[]){
    ARGS_CHECK(argc,2);
    int fd_read = open(argv[1],O_RDONLY);
    ERROR_CHECK(fd_read,-1,"open");
    printf("read side is opened.\n");
    close(fd_read);
    return 0;
}
