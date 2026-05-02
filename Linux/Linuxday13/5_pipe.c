#include "49func.h"
int main() {
  int fds[2];
  pipe(fds);
  printf("fds[0] = %d, fds[1] = %d\n", fds[0], fds[1]);
  if (fork() == 0) {
    // 子进程
    // 子进程关闭写端
    close(fds[1]);
    char buf[1024] = {0};
    read(fds[0], buf, sizeof(buf));
    printf("这里是子进程,buf = %s\n", buf);
    close(fds[0]);
    exit(0);
  } else {
    // 父进程
    close(fds[0]);
    write(fds[1], "hello", 5);
    wait(NULL);
    close(fds[1]);
    exit(0);
  }
  return 0;
}
