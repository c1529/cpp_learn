#include "49func.h"
int main() {
  pthread_mutex_t mutex;
  pthread_cond_t cond;
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond, NULL);
  pthread_mutex_lock(&mutex);
  time_t now = time(NULL);
  printf("before time =%s\n", ctime(&now));
  struct timespec abstime;
  abstime.tv_sec = now + 10; // 加上10秒
  abstime.tv_nsec = 0;
  pthread_cond_timedwait(&cond, &mutex, &abstime);
  pthread_mutex_unlock(&mutex);
  now = time(NULL);
  printf("after time =%s\n", ctime(&now));
  return 0;
}
