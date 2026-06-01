#include "head.h"
int exitpipe[2];
void sigFunc(int signum){
    printf("process pool is going to exit\n");
    write(exitpipe[1],"1",1);
}
int main(int argc, char *argv[])
{
    // ./server 0.0.0.0 1234 3
    ARGS_CHECK(argc,4);
    int workerNum = atoi(argv[3]);
    workerdata_t * workerdataArr = (workerdata_t*)calloc(workerNum,sizeof(workerdata_t));
    makeWorker(workerNum,workerdataArr);
    pipe(exitpipe);
    signal(SIGUSR1,sigFunc);
    int sockfd;
    tcpInit(&sockfd,argv[1],argv[2]);
    int epfd = epoll_create(1);
    epollAdd(epfd,sockfd);
    //监听exitpipe的读端
    epollAdd(epfd,exitpipe[0]);
    // 每个子进程的socketfd
    // 可能用来监听子进程给父进程发送的消息？？？？
    for(int i=0;i<workerNum;i++){
        epollAdd(epfd,workerdataArr[i].socketfd);
    }
    int readyMax=workerNum+1;
    while(1){
        struct epoll_event *readySet=(struct epoll_event *)calloc(readyMax,sizeof(struct epoll_event));
        int readyNum =epoll_wait(epfd,readySet,readyMax,-1);
        for(int i=0;i<readyNum;i++){
            if(readySet[i].data.fd==sockfd){
                // 客户端接入
                printf("master,client connect\n");
                int netfd = accept(sockfd,NULL,NULL);
                // 发送一个空闲的子进程
                for(int j=0;j<workerNum;j++){
                    if(workerdataArr[j].status==FREE){
                        printf("No %d worker got his job, pid = %d\n",j,workerdataArr[j].pid);
                        sendfd(workerdataArr[j].socketfd,netfd);//workerdataArr[j].socketfd是父子进程通信的
                                                                //netfd 子进程处理父进程TCP连接的客户端
                        workerdataArr[j].status=BUSY;
                        break;
                    }
                }
                // 如果子进程都在忙 那就直接关闭（变相的直接拒绝客户端连接）
                close(netfd);//因为子进程也引用了这个netfd，所引这里netfd只会减少一次引用
            }
            else if(readySet[i].data.fd==exitpipe[0]){
                // 子进程终止的逻辑
                for(int j=0;j<workerNum;j++){
                    kill(workerdataArr[j].pid,SIGKILL);
                    printf("kill 1 worker! pid = %d\n",workerdataArr[j].pid);
                }
                for(int j=0;j<workerNum;j++){
                    wait(NULL);
                }
                printf("master is going to exit!\n");
                exit(0);
            }
            else{// 说明子进程完成任务
                printf("master, 1 child finished his job\n");
                for(int j=0;j<workerNum;j++){
                    if(workerdataArr[j].socketfd==readySet[i].data.fd){
                        pid_t pid;
                        read(workerdataArr[j].socketfd,&pid,sizeof(pid));
                        printf("No %d worker, pid = %d\n",j,pid);
                        workerdataArr[j].status=FREE;
                        break;
                    }
                }
            }
        }
    }
    return 0;
}

