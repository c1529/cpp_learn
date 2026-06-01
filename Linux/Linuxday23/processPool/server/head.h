#include<49func.h>
enum{
    FREE,
    BUSY
};
typedef struct workerdata_s{//父进程使用，用来保存每个子进程信息
    pid_t pid;
    int status;
    int socketfd;//父子进程通信的
}workerdata_t;
int makeWorker(int workerNum,workerdata_t * workerdataArr);
int eventLoop(int sockfd);
int tcpInit(int *psockfd,const char *ip,const char *port);
int epollAdd(int epfd,int fd);
int epollDel(int epfd,int fd);
int sendfd(int sockfd,int fdtosend);
int recvfd(int sockfd,int *pfdtorecv);
int transFile(int netfd);
