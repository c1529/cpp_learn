#include "49func.h"
typedef struct node_s {
  int data;
  struct node_s *pNext;
} node_t;
typedef struct queue_s {
  node_t *pFront;
  node_t *pRear;
  int queueSize;
} queue_t;

void enQueue(queue_t *pqueue, int data) {
  // 入队
  node_t *pNew = (node_t *)calloc(1, sizeof(node_t));
  pNew->data = data;
  if (pqueue->queueSize == 0) {
    pqueue->pFront = pNew;
    pqueue->pRear = pNew;
  } else {
    pqueue->pRear->pNext = pNew;
    pqueue->pRear = pNew;
  }
  (pqueue->queueSize)++;
}
void deQueue(queue_t *pqueue) {
  node_t *pCur = pqueue->pFront;
  pqueue->pFront = pCur->pNext;
  free(pCur);
  (pqueue->queueSize)--;
  if (pqueue->pFront == NULL) {
    pqueue->pRear = NULL;
  }
}
void visitQueue(queue_t *pqueue) {
  node_t *pCur = pqueue->pFront;
  while (pCur) {
    printf("%d ", pCur->data);
    pCur = pCur->pNext;
  }
  printf("\n");
}
/*
int main() {
  queue_t queue;
  memset(&queue, 0, sizeof(queue)); // 初始化
  int data;
  for (int i = 0; i < 8; i++) {
    data = rand() % 1000;
    enQueue(&queue, data);
    printf("data = %d\n", data);
    visitQueue(&queue);
  }
  for (int i = 0; i < 8; i++) {
    deQueue(&queue);
    visitQueue(&queue);
  }
  return 0;
}
*/
typedef struct shareRes_s {
  queue_t queue;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
} shareRes_t;
void *producer(void *arg) { // 生产者
  shareRes_t *pShareRes = (shareRes_t *)arg;
  while (1) { // 不断生产
    pthread_mutex_lock(&pShareRes->mutex);
    while (pShareRes->queue.queueSize >= 10) {
      pthread_cond_wait(&pShareRes->cond, &pShareRes->mutex);
    }
    int data = rand() % 1000;
    printf("Before producer , queueSize = %d, data = %d\n",
           pShareRes->queue.queueSize, data);
    enQueue(&pShareRes->queue, data);
    printf("After producer ");
    visitQueue(&pShareRes->queue);
    pthread_cond_broadcast(&pShareRes->cond);
    pthread_mutex_unlock(&pShareRes->mutex);
    sleep(3);
  }
}
void *consumer(void *arg) { // 消费者
  sleep(5);
  shareRes_t *pShareRes = (shareRes_t *)arg;
  while (1) {
    pthread_mutex_lock(&pShareRes->mutex);
    while (pShareRes->queue.queueSize <= 0) {
      pthread_cond_wait(&pShareRes->cond, &pShareRes->mutex);
    }
    int data = pShareRes->queue.pFront->data;
    printf("Before consumer , queueSize = %d, pFront = %d\n",
           pShareRes->queue.queueSize, data);
    deQueue(&pShareRes->queue);
    printf("After consumer ");
    visitQueue(&pShareRes->queue);
    pthread_cond_broadcast(&pShareRes->cond);
    pthread_mutex_unlock(&pShareRes->mutex);
    sleep(1);
  }
}
int main() {
  shareRes_t shareRes;
  memset(&shareRes.queue,0,sizeof(queue_t));
  // 初始有8个商品
  int data;
  for (int i = 0; i < 8; i++) {
    data = rand() % 1000;
    enQueue(&shareRes.queue, data);
    printf("data = %d\n", data);
    visitQueue(&shareRes.queue);
  }
  pthread_mutex_init(&shareRes.mutex, NULL);
  pthread_cond_init(&shareRes.cond, NULL);
  pthread_t tid1, tid2, tid3, tid4, tid5;
  pthread_create(&tid1, NULL, producer, &shareRes);
  pthread_create(&tid2, NULL, producer, &shareRes);
  pthread_create(&tid3, NULL, producer, &shareRes);
  pthread_create(&tid4, NULL, consumer, &shareRes);
  pthread_create(&tid5, NULL, consumer, &shareRes);
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  pthread_join(tid3,NULL);
  pthread_join(tid4,NULL);
  pthread_join(tid5,NULL);
  return 0;
}
