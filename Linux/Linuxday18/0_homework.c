#include "49func.h"
// 输出顺序是 A B C
typedef struct shareRes_s {
  int flag; // 0-->A 1-->B 2-->C
  pthread_mutex_t mutex;
  pthread_cond_t cond; // 主要是实现无竞争
} shareRes_t;
void *threadFunc(void *arg) {
  shareRes_t *pshareRes = (shareRes_t *)arg;
  pthread_mutex_lock(&pshareRes->mutex);
  while (pshareRes->flag == 0) {
    pthread_cond_wait(&pshareRes->cond, &pshareRes->mutex);
  }
  printf("B\n");
  pshareRes->flag = 2;
  pthread_cond_signal(&pshareRes->cond);
  pthread_mutex_unlock(&pshareRes->mutex);
  pthread_exit(NULL);
}
int main() {
  shareRes_t shareRes;
  shareRes.flag = 0;
  pthread_mutex_init(&shareRes.mutex, NULL);
  pthread_cond_init(&shareRes.cond, NULL);
  pthread_t tid;
  pthread_create(&tid, NULL, threadFunc, &shareRes);
  printf("A\n");
  pthread_mutex_lock(&shareRes.mutex);
  shareRes.flag = 1;
  pthread_cond_signal(&shareRes.cond);
  pthread_mutex_unlock(&shareRes.mutex);
  pthread_mutex_lock(&shareRes.mutex);
  while (shareRes.flag == 1) {
    pthread_cond_wait(&shareRes.cond, &shareRes.mutex);
  }
  printf("C\n");
  pthread_mutex_unlock(&shareRes.mutex);
  pthread_join(tid, NULL);
  return 0;
}
