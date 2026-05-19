#include "49func.h"
void sigFunc(int signum) {
  printf("before signum = %d\n", signum);
  sleep(5);
  printf("after signum = %d\n", signum);
}
int main() {
  struct sigaction act;
  memset(&act, 0, sizeof(act));
  act.sa_handler = sigFunc;
  act.sa_flags = SA_RESTART;
  sigaddset(&act.sa_mask,SIGQUIT); // 执行sigFunc时候临时加入3号屏蔽
  sigaction(SIGINT, &act, NULL);
  char buf[4096] = {0};
  read(STDIN_FILENO, buf, sizeof(buf));
  printf("buf = %s\n", buf);
  return 0;
}
