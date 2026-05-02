#include "49func.h"
void sigFunc(int signum) { 
    printf("signum = %d\n", signum); 
    signal(SIGINT,SIG_DFL);//恢复2号信号默认
}
int main() {
  sleep(10);
  printf("sleep over\n");
  // 2号行为是 ctrl+c
  signal(2, sigFunc); // 修改2号信号的递送行为
  while (1)
    ;
  return 0;
}
