#include "49func.h"
int global = 0;
void *threadFunc(void *arg) {
  printf("global = %d\n", global);
  global++;
}

int main() {
  pthread_t pid;
  pthread_create(&pid, NULL, threadFunc, NULL);
  sleep(2);
  printf("global = %d\n", global);
  return 0;
}
