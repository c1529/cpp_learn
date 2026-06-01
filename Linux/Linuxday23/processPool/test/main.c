#include <49func.h>
int sendfd(int sockfd,int fdtosend);
int recvfd(int sockfd,int *pfdtorecv);
int main(int argc, char *argv[])
{
    int fds[2];
    socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
    if(fork()==0){
        int fd = open("file1",O_RDWR);
        sendfd(fds[1],fd);
        printf("child fd = %d\n",fd);
    }else{
        int fd1 = open("file2",O_RDWR);
        int fd2;
        recvfd(fds[0],&fd2);
        printf("parent fd1 = %d, fd2 = %d\n",fd1,fd2);
        wait(NULL);
    }
    return 0;
}

