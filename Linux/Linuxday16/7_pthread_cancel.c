#include "49func.h"
void *threadFunc(void *arg) {
  while (1) {
    //printf("i still alive\n"); // printf属于取消点函数
    pthread_testcancel();//手动设置的取消点函数 什么也不干就可以退出线程
  }
}
int main() {
  pthread_t tid;
  pthread_create(&tid, NULL, threadFunc, NULL);
  sleep(1);
  printf("main : sleep over\n");
  pthread_cancel(tid); // 发送取消请求 子线程遇到取消点函数就会终止
  void *ret;
  pthread_join(tid, &ret);
  printf("you die,ret = %ld\n", (long)ret);
  return 0;
}
