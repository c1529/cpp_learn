#ifndef __THREAD_POOL__
#define __THREAD_POLL__
#include<49func.h>
#include"taskQueue.h"
//主线程维持每一个子线程的信息
typedef struct threadPool_s{
    //子线程的数据
    pthread_t *tidArr;
    int workerNum;
    //任务队列
    queue_t taskQueue;
    //锁
    pthread_mutex_t mutex;
    //条件变量
    pthread_cond_t cond;
}threadPool_t;
int makeWorker(threadPool_t *pthreadPool);
void *threadFunc(void* arg);
 int Enqueue(queue_t *pqueue,int fd);
 int Dequeue(queue_t *pqueue);
 int tcpInit(int *psockfd,const char *ip,const char *port);
 int epollAdd(int epfd,int fd);
 int epollDel(int epfd,int fd);
 int transFile(int netfd);
#endif
