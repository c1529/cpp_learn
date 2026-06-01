// 基于链表实现队列 数据域是int
#include<49func.h>
typedef struct node_s{
    int fd;
    struct node_s * pnext;
}node_t;
typedef struct queue_s {
node_t * pfront;
node_t *prear;
int queueSize;
}queue_t;
int Enqueue(queue_t *pqueue,int fd);
int Dequeue(queue_t *pqueue);
