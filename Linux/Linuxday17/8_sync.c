#include "49func.h"
typedef struct shareRes_s {
  int flag;              // 0-->B不能运行 0-->B可以运行
  pthread_mutex_t mutex; // 保护flag锁
  pthread_cond_t cond;   // 条件变量 提供一个无竞争的同步机制
} shareRes_t;
void *threadFunc(void *arg) {
  shareRes_t *pshareRes = (shareRes_t *)arg;
  // 先上锁
  pthread_mutex_lock(&pshareRes->mutex);
  if (pshareRes->flag != 1) { // B不能执行
    pthread_cond_wait(&pshareRes->cond, &pshareRes->mutex);
    //这个函数调用前需要上锁
    //唤醒前会解锁mutex 并且会阻塞cond这个变量(其他线程会通过唤醒cond来唤醒该函数)
    //唤醒后会进行上锁mutex
  }
  printf("B is begin\n");
  sleep(3);
  printf("B is end\n");
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
  sleep(5);
  printf("A is begin\n");
  sleep(3);
  printf("A is end\n");
  pthread_mutex_lock(&shareRes.mutex);
  shareRes.flag = 1;
  pthread_cond_signal(&shareRes.cond);
  pthread_mutex_unlock(&shareRes.mutex);
  pthread_join(tid, NULL);
  return 0;
}
