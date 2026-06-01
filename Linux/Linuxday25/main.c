#include"threadPool.h"
// ./192.168.182.129 1234 3
int main(int argc, char *argv[])
{
    ARGS_CHECK(argc,4);
    int workerNum=atoi(argv[3]);
    threadPool_t threadPool;
    threadPool.tidArr=(pthread_t *)calloc(workerNum,sizeof(pthread_t));
    threadPool.workerNum=workerNum;
    pthread_mutex_init(&threadPool.mutex,NULL);
    pthread_cond_init(&threadPool.cond,NULL);
    bzero(&threadPool.taskQueue,sizeof(queue_t));
    makeWorker(&threadPool);
    
    int sockfd;
    tcpInit(&sockfd,argv[1],argv[2]);
    int epfd=epoll_create(1);
    epollAdd(epfd,sockfd);
    while(1){
        struct epoll_event readySet[1];
        int readyNum=epoll_wait(epfd,readySet,1,-1);
        for(int i=0;i<readyNum;i++){
            if(readySet[i].data.fd==sockfd){
                int netfd=accept(sockfd,NULL,NULL);
                pthread_mutex_lock(&threadPool.mutex);
                Enqueue(&threadPool.taskQueue,netfd);
                printf("master send a task!\n");
                pthread_cond_signal(&threadPool.cond);
                pthread_mutex_unlock(&threadPool.mutex);
            }
        }
    }

    return 0;
}

