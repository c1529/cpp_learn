#include "49func.h"
int main() {
  // 创建子进程,子进程执行0_homework_2  
  if (fork() == 0) {
    execl("0_homework_2", "./0_homework_2",NULL);
  } else {
    wait(NULL);
  }
  return 0;
}
