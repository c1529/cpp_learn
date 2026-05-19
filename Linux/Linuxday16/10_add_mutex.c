#include "49func.h"
#define NUM 10000000
typedef struct shareRes_s {
  int num;
  pthread_mutex_t mutex;
} shareRes_t;
void *threadFunc(void *arg) {
  shareRes_t *PShareRes = (shareRes_t *)arg;
  for (int i = 0; i < NUM; i++) {
    pthread_mutex_lock(&PShareRes->mutex);
    (PShareRes->num)++;
    pthread_mutex_unlock(&PShareRes->mutex);
  }
  pthread_exit(NULL);
}

int main() {
  shareRes_t shareRes;
  shareRes.num = 0;
  pthread_mutex_init(&shareRes.mutex, NULL); // 初始化锁
  pthread_t tid;
  shareRes.num = 0;
  pthread_create(&tid, NULL, threadFunc, &shareRes);
  for (int i = 0; i < NUM; i++) {
    pthread_mutex_lock(&shareRes.mutex);
    shareRes.num++;
    pthread_mutex_unlock(&shareRes.mutex);
  }
  pthread_join(tid, NULL);
  printf("shareRes.num = %d\n", shareRes.num);
  return 0;
}
