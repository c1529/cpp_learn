#include "49func.h"
void *threadFunc(void *arg) {
  // arg接受了传入的参数 pHeap
  // void* 传入什么类型的参数就恢复什么类型的
  int *pHeap = (int *)arg;
  printf("i am child,*pHeap = %d\n", *pHeap);
  (*pHeap)++;
}
int main() {
  int *pHeap = (int *)malloc(sizeof(int));
  *pHeap = 1;
  pthread_t pid;
  pthread_create(&pid, NULL, threadFunc, pHeap);
  sleep(2);
  printf("i am main,*pHeap = %d\n", *pHeap);
  return 0;
}
