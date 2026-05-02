#include "49func.h"
int main() {
  printf("hello\n");
  pid_t pid;
  pid = fork();
  if (pid == -1) {
    printf("创建fork失败\n");
  } else if (pid == 0) {
    // 子进程
    printf("这是子进程\n");
    printf("pid = %d , ppid = %d\n", getpid(), getppid());
  } else {
    wait(NULL);//父进程专属 等待字进程结束后执行
    printf("这是父进程\n");
    printf("pid = %d , ppid = %d\n", getpid(), getppid());
    wait(NULL);//父进程专属 等待字进程结束后执行
  }
  return 0;
}
