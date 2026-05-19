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
  // SA_RESTART 会让信号处理函数执行完毕后，内核重新执行被中断的 read 系统调用
  // 没有SA_RESTART 会导致处理信号函数后 read直接返回-1 这时buf为空
  //act.sa_flags = SA_RESTART;
  // SA_RESETHAND表示执行一次之后，信号恢复默认
  act.sa_flags = SA_RESTART|SA_RESETHAND;
  sigaction(SIGINT, &act, NULL);
  // while (1);
  char buf[4096] = {0};
  read(STDIN_FILENO, buf, sizeof(buf));
  printf("buf = %s\n", buf);
  return 0;
}
