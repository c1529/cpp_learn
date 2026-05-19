#include "49func.h"
void *threadFunc(void *arg) { printf("i am child thread\n"); }
int main() {
  pthread_t tid; // 用于保存子线程的tid
  pthread_create(&tid, NULL, threadFunc, NULL);
  // 创建一个子线程，线程id保存到tid中，线程默认属性是NULL
  // 线程启动函数是threadFunc,启动函数的参数是NULL
  printf("i am main thread\n");
  sleep(1);
  printf("tid = %ld\n", tid);
  return 0;
}
