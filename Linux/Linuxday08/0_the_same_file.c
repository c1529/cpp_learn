#include"49func.h"
int main(int argc,char* argv[]){
    // ./0_the_same_file file1 file2
    ARGS_CHECK(argc,3);
    int fd1 = open(argv[1],O_RDONLY);
    int fd2 = open(argv[2],O_RDONLY);
    ERROR_CHECK(fd1,-1,"fd1_open");
    ERROR_CHECK(fd2,-1,"fd2_open");

    char buf1[4096];
    char buf2[4096];

    while(1){
        ssize_t ret1 = read(fd1,buf1,4096);
        ssize_t ret2 = read(fd2,buf2,4096);
        if(ret1==-1||ret2==-1){
            printf("failed in read.\n");
            exit(1);
        }
        if(ret1==0&&ret2==0) break;
        if(ret1!=ret2){
            printf("The not same.\n");
            close(fd1);
            close(fd2);
            return 0;
        }else{
            for(int i=0;i<ret1;i++)
                if(buf1[i]!=buf2[i]){
                    printf("The not same.\n");
                    close(fd1);
                    close(fd2);
                    return 0;
                }
        }
    }
    close(fd1);
    close(fd2);
    printf("The same.\n");
    return 0;
}
