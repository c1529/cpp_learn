#include "49func.h"
// 实现两个窗口进行卖票
typedef struct shareRes_s {
  int ticket;
  int flag; // 表示是否可以加票 0不可以  1可以
  pthread_mutex_t mutex;
} shareRes_t;
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
    if (pshareRes->ticket <= 10) {
      pshareRes->flag = 1;
    }
    pthread_mutex_unlock(&pshareRes->mutex);
    sleep(1);
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
    if (pshareRes->ticket <=10) {
      pshareRes->flag = 1;
    }
    pthread_mutex_unlock(&pshareRes->mutex);
    sleep(1);
  }
  pthread_exit(NULL);
}
void *addsticket(void *arg) {
  shareRes_t *pshareRes = (shareRes_t *)arg;
  while (1) {
    pthread_mutex_lock(&pshareRes->mutex);
    if (pshareRes->flag != 0) {
      // 加票
      pshareRes->ticket += 10;
      printf("ticket is add\n");
      pthread_mutex_unlock(&pshareRes->mutex);
      break;
    }
    pthread_mutex_unlock(&pshareRes->mutex);
  }
  pthread_exit(NULL);
}
int main() {
  shareRes_t shareRes;
  shareRes.ticket = 20;
  shareRes.flag = 0; // 最开始不用加票
  pthread_mutex_init(&shareRes.mutex, NULL);
  pthread_t tid1, tid2, tid3;
  pthread_create(&tid1, NULL, sellWindow1, &shareRes);
  pthread_create(&tid2, NULL, sellWindow2, &shareRes);
  pthread_create(&tid3, NULL, addsticket, &shareRes);
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_join(tid3, NULL);
  return 0;
}
