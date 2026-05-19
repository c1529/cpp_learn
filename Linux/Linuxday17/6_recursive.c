#include "49func.h"
void *threadFunc(void *arg) {
  pthread_mutex_t *pmutex = (pthread_mutex_t *)arg;
  pthread_mutex_lock(pmutex);
  printf("i am child\n");
  pthread_mutex_unlock(pmutex);
}
int main() {
  pthread_mutexattr_t mutexattr;      // 声明锁的属性
  pthread_mutexattr_init(&mutexattr); // 初始化锁的属性
  // 设置锁的属性->可重入锁锁(一个线程可以多次上锁，+1 +2 +3...)
  pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE);
  // 用锁的属性初始化锁
  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, &mutexattr);

  // 主线程先后两次上锁
  int ret = pthread_mutex_lock(&mutex);
  THREAD_ERROR_CHECK(ret, "mutex_lock 1");
  printf("lock once!\n");
  ret = pthread_mutex_lock(&mutex);
  THREAD_ERROR_CHECK(ret, "mutex_lock 2");
  printf("lock twice!\n");

  // 创建一个线程
  pthread_t tid;
  pthread_create(&tid, NULL, threadFunc, &mutex);
  sleep(2);
  printf("sleep over1\n");
  pthread_mutex_unlock(&mutex);
  sleep(2);
  printf("sleep over2\n");
  pthread_mutex_unlock(&mutex);
  pthread_join(tid,NULL);
  return 0;
}
