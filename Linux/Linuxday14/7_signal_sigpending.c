#include "49func.h"
void sigFunc(int signum) {
  printf("before signum = %d\n", signum);
  sleep(5);
  // 检查是否存在未决的2号信号
  sigset_t pending;
  sigpending(&pending);
  if (sigismember(&pending, SIGINT)) {
    printf("SIGINT is pending\n");
  } else {
    printf("SIGINT is not pending\n");
  }
  printf("after signum = %d\n", signum);
}
int main() {
  signal(SIGINT, sigFunc);
  while (1) {
    sleep(1);
  }
}
