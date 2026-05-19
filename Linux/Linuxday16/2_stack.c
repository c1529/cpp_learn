#include "49func.h"
void *threadFunc(void *arg) {
  int *pstack = (int *)arg;
  printf("i am child,stack = %d\n", *pstack);
  (*pstack)++;
}
int main() {
  int stack = 100;
  pthread_t pid;
  pthread_create(&pid, NULL, threadFunc, &stack);
  sleep(2);
  printf("i am main,stack = %d\n", stack);
  return 0;
}
