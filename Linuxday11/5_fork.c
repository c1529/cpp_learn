#include "49func.h"
int main() {
  // printf 1. 将数据拷贝到STDOUT中
  //        2. 遇到换行符或缓冲区满了，STDOUT会拷贝到文件对象里面(输出到屏幕)
  printf("hello");
  // fork会拷贝一份FILE
  fork();
  printf("world\n");
  return 0;
}
