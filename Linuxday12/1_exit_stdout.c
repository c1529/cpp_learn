#include "49func.h"
int main() {
  printf("hello world");// printf函数 文件流里面满了或者遇到换行符才会输出
  //exit(1);//exit() return 会直接输出文件流里面的内容
  _exit(1);// 不会输出文件流里面的内容 直接kill进程
}
