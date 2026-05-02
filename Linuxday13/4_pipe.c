#include "49func.h"
int main() {
  int fds[2];
  pipe(fds);
  printf("fds[0] = %d, fds[1] = %d\n", fds[0], fds[1]);
  // fds[0] ---> 读端
  // fds[1] ---> 写端
  char buf[1024] = {0};
  write(fds[1], "hello", 5);
  read(fds[0], buf, sizeof(buf));
  printf("buf = %s\n", buf);
  return 0;
}
