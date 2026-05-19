#include "49func.h"
void sigFunc(int signum) { printf("signum = %d\n", signum); }
int main() {
  // alarm 和 pause 配合可实现sleep效果
  alarm(10);
  signal(SIGALRM, sigFunc);
  pause(); // 无限阻塞等待任意一个信号，然后运行
  return 0;
}
