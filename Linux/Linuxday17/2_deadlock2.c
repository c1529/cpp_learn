#include "49func.h"
pthread_mutex_t mutex;
void *threadFunc(void *arg) {
  pthread_mutex_lock(&mutex);
  printf("i am child\n");
  pthread_exit(NULL);
}
int main() {
  pthread_t tid;
  pthread_mutex_init(&mutex, NULL);
  pthread_create(&tid, NULL, threadFunc, NULL);
  sleep(2);
  pthread_mutex_lock(&mutex);
  printf("i am parent\n");
  pthread_mutex_unlock(&mutex);
  pthread_join(tid, NULL);
  return 0;
}
