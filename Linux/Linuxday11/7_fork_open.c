#include "49func.h"
int main() {
  // 先open后fork 父进程和子进程共享一个fd ,同时文件偏移量也会共享
  // 先fork后open 父进程和子进程不会共享文件偏移量，这会导致后面写的覆盖前面写的
  int fd = open("file1", O_WRONLY);
  if (fork() == 0) {
    // 子进程
    write(fd, "hello", 5);

  } else {
    sleep(2);
    // 父进程
    write(fd, "world", 5);
  }
  close(fd);

  return 0;
}
