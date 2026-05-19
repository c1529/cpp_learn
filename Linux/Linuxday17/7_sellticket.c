#include "49func.h"
// 实现两个窗口进行卖票
typedef struct shareRes_s {
  int ticket;
  pthread_mutex_t mutex;
} shareRes_t;
/*
//会导致卖票出现-1，因为没有锁上ticket
void *sellWindow1(void *arg) {
  shareRes_t *pshareRes = (shareRes_t *)arg;
  while (pshareRes->ticket > 0) {
    pthread_mutex_lock(&(pshareRes->mutex));
    printf("before window1 sell a ticket,ticket=%d\n", pshareRes->ticket);
    (pshareRes->ticket)--;
    printf("after window1 sell a ticket,ticket=%d\n", pshareRes->ticket);
    pthread_mutex_unlock(&(pshareRes->mutex));
  }
  pthread_exit(NULL);
}
void *sellWindow2(void *arg) {
  shareRes_t *pshareRes = (shareRes_t *)arg;
  while (pshareRes->ticket > 0) {
    pthread_mutex_lock(&(pshareRes->mutex));
    printf("before window2 sell a ticket,ticket=%d\n", pshareRes->ticket);
    (pshareRes->ticket)--;
    printf("after window2 sell a ticket,ticket=%d\n", pshareRes->ticket);
    pthread_mutex_unlock(&(pshareRes->mutex));
  }
  pthread_exit(NULL);
}
*/
void *sellWindow1(void *arg) {
  shareRes_t *pshareRes = (shareRes_t *)arg;
  while (1) {
    pthread_mutex_lock(&pshareRes->mutex);
    if (pshareRes->ticket <= 0) {
      // 如果票不够
    pthread_mutex_unlock(&pshareRes->mutex);
        break;
    }
    printf("before window1 sell a ticket,ticket=%d\n", pshareRes->ticket);
    (pshareRes->ticket)--;
    printf("after window1 sell a ticket,ticket=%d\n", pshareRes->ticket);
    pthread_mutex_unlock(&pshareRes->mutex);
  }
  pthread_exit(NULL);
}
void *sellWindow2(void *arg) {
  shareRes_t *pshareRes = (shareRes_t *)arg;
  while (1) {
    pthread_mutex_lock(&pshareRes->mutex);
    if (pshareRes->ticket <= 0) {
      // 如果票不够
    pthread_mutex_unlock(&pshareRes->mutex);
        break;
    }
    printf("before window2 sell a ticket,ticket=%d\n", pshareRes->ticket);
    (pshareRes->ticket)--;
    printf("after window2 sell a ticket,ticket=%d\n", pshareRes->ticket);
    pthread_mutex_unlock(&pshareRes->mutex);
  }
  pthread_exit(NULL);
}
int main() {
  shareRes_t shareRes;
  shareRes.ticket = 20;
  pthread_mutex_init(&shareRes.mutex, NULL);
  pthread_t tid1, tid2;
  pthread_create(&tid1, NULL, sellWindow1, &shareRes);
  pthread_create(&tid2, NULL, sellWindow2, &shareRes);
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  return 0;
}
