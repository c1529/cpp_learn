#include "49func.h"
void *threadFunc(void *arg) {
  long val = (long)arg;
  printf("i am child, val = %ld\n", val);
}
int main() {
  long val = 1000;
  pthread_t tid;
  // void* 和 long 都是八字节长度 可以直接传递
  pthread_create(&tid, NULL, threadFunc, (void *)val);
  sleep(2);
  return 0;
}
