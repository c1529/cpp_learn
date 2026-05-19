#include "49func.h"
int main() {
  alarm(10); // 10秒后调用alarm函数，进程终止
  while (1) {
    printf("10_alarm is runing...\n");
    sleep(1);
  }
  return 0;
}
