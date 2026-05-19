#include "49func.h"
void sigFunc(int signum) {
  printf("before,signum = %d\n", signum);
  sleep(10);
  printf("after,signum= %d \n", signum);
}
int main() {
  signal(SIGINT, sigFunc);
  signal(SIGQUIT, sigFunc);
  while (1) {
    sleep(1);
  }
  return 0;
}
