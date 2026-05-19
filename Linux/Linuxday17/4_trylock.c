#include "49func.h"
pthread_mutex_t mutex;
void *threadFunc(void *arg) {
  sleep(1);
  while (1) {

    int ret = pthread_mutex_trylock(&mutex);
    THREAD_ERROR_CHECK(ret, "trylock child");
    if (ret == 0) {
      break;
    }
  }
  sleep(2);
  printf("child thread,sleep over\n");
  pthread_mutex_unlock(&mutex);
  pthread_exit(NULL);
}

int main() {
  pthread_t tid;
  pthread_mutex_init(&mutex, NULL);
  pthread_create(&tid, NULL, threadFunc, NULL);
  int ret = pthread_mutex_trylock(&mutex);
  THREAD_ERROR_CHECK(ret, "trylock main");
  sleep(3);
  printf("main thread,sleep over\n");
  pthread_mutex_unlock(&mutex);
  pthread_join(tid, NULL);
  return 0;
}
