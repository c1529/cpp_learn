#include"head.h"
int makeWorker(int workerNum,workerdata_t * workerdataArr){
    pid_t pid;
    int fds[2];
    for(int i=0;i<workerNum;i++){
        socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
        pid = fork();
        if(pid==0){
            //子进程
            close(fds[0]);
            eventLoop(fds[1]);
        }
        close(fds[1]);
        //父进程
        workerdataArr[i].pid=pid;
        workerdataArr[i].status=FREE;
        workerdataArr[i].socketfd=fds[0];
        printf("worker %d,pid = %d,socketfd = %d\n",i,pid,fds[0]);
    }
    return 0;
}
int eventLoop(int sockfd){
    while(1){
        // 接收任务
        int netfd;
        recvfd(sockfd,&netfd);
        // 写业务代码 通过netfd和客户端通信
        printf("child begins working!\n");
        sleep(3);
        transFile(netfd);
        close(netfd);
        printf("child finished his job\n");
        pid_t pid=getpid();
        write(sockfd,&pid,sizeof(pid));
    }
}
