#include"49func.h"
#define LENGTH 10
int main(int argc,char *argv[]){
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    char *p = (char *)mmap(NULL,LENGTH,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(p==MAP_FAILED){   //mmap失败返回的是MAP_FAILED
        printf("mmap is failed.\n");
        exit(1);
    }
    for(int i=0;i<LENGTH;i++){
        printf("%c\n",p[i]);
    }
    p[4] = 'O';//直接修改
    for(int i=0;i<LENGTH;i++){
        printf("%c",p[i]);
    }
    munmap(p,LENGTH);
    close(fd);
    return 0;
}
