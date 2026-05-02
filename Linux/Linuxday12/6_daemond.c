#include "49func.h"
void Daemon() {
  if (fork() != 0) {
    // 父进程
    exit(1);
  }
  // 子进程
  setsid();
  // 关闭输入输出
  for (int i = 0; i <= 2; i++) {
    close(i);
  }
  // 修改进程的启动环境属性
  chdir("/");
  umask(0);
}
int main() {
  Daemon();
  for (int i = 0; i < 100; i++) {
    syslog(LOG_INFO, "hello world! i = %d",i);
    sleep(2);
  }
  return 0;
}
