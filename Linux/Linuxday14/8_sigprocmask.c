#include "49func.h"
int main() {
  sigset_t set, oldset;
  sigfillset(&set);                      // 把所有信号存入到set中
  sigprocmask(SIG_BLOCK, &set, &oldset); // 屏蔽所有信号(但是不包含9号等信号)
  printf("block all\n");
  sleep(10);
  printf("unblock all\n");
  sigprocmask(SIG_SETMASK, &oldset, NULL);
  while (1) {
    sleep(1);
  }
  return 0;
}
