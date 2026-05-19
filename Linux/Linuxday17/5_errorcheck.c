#include "49func.h"
int main() {
  pthread_mutexattr_t mutexattr;      // 声明锁的属性
  pthread_mutexattr_init(&mutexattr); // 初始化锁的属性
  // 设置锁的属性->检测锁
  pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_ERRORCHECK);
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
  return 0;
}
