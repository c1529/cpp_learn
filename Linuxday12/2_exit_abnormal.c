#include "49func.h"
int main() {
  if (fork() == 0) {
    while (1);
  } else {
    int wstatus;
    wait(&wstatus); // 获取子进程终止状态
    if (WIFEXITED(wstatus)) {
      printf("exit normally,exit code = %d\n", WIFEXITED(wstatus));
    } else if (WIFSIGNALED(wstatus)) {
      printf("exit abnormally, termal sig = %d\n", WTERMSIG(wstatus));
    }
  }
  return 0;
}
