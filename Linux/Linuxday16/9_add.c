#include "49func.h"
#define NUM 10000000
void *threadFunc(void *arg) {
  int *pnum = (int *)arg;
  for (int i = 0; i < NUM; i++) {
    (*pnum)++;
  }
  pthread_exit(NULL);
}

int main() {
  pthread_t tid;
  int num = 0;
  pthread_create(&tid, NULL, threadFunc, &num);
  for (int i = 0; i < NUM; i++) {
    num++;
  }
  pthread_join(tid, NULL);
  printf("num = %d\n", num);
  return 0;
}
