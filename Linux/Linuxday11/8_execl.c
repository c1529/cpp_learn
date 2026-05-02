#include "49func.h"
int main() {
  printf("you can see me\n");
  execl("add", "./add", "3", "4", NULL);
  // 可执行程序的路径 命令行的参数
  printf("you can not see me\n");
  return 0;
}
