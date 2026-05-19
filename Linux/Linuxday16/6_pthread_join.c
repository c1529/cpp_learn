#include "49func.h"
void *threadFunc(void *arg) {
  printf("i am child\n");
  return (void *)0;
}
int main() {
  pthread_t tid;
  pthread_create(&tid, NULL, threadFunc, NULL);
  void *ret;
  // pthread_join 类似wait 会等待子线程的终止
  pthread_join(tid, &ret);
  printf("ret = %ld\n", (long)ret);
  return 0;
}
