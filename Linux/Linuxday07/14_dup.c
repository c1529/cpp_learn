#include"49func.h"
int main(int argc,char* argv[]){
    // ./14_dup file
    ARGS_CHECK(argc,2);
    int old_fd = open(argv[1],O_RDWR);
    ERROR_CHECK(old_fd,-1,"open");
    int new_fd = dup(old_fd);
    ERROR_CHECK(new_fd,-1,"dup");
    printf("old_fd = %d\n",old_fd);
    printf("new_fd = %d\n",new_fd);
    write(old_fd,"hello",5);
    write(new_fd,"world",5);
    close(new_fd);
    close(old_fd);
    return 0;
}




