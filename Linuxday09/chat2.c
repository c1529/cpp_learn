#include "49func.h"
int main(int argc, char *argv[]) {
  // ./chat1 1.pipe 2.pipe
  ARGS_CHECK(argc, 3);
  int fdw = open(argv[1],O_WRONLY);
  int fdr = open(argv[2],O_RDONLY);
  ERROR_CHECK(fdw, -1, "open fdw");
  ERROR_CHECK(fdr, -1, "open fdr");
  printf("chat is established!\n");
  char buf[4096];
  fd_set rdset;           // 创建一个监听集合
  struct timeval timeout; // 关于超时机制
  while (1) {
    // 初始化
    FD_ZERO(&rdset);
    FD_SET(STDIN_FILENO, &rdset);
    FD_SET(fdr, &rdset);
    // 调用select 使进程阻塞
    timeout.tv_sec = 3;
    timeout.tv_usec = 0;
    int ret = select(fdr + 1, &rdset, NULL, NULL, &timeout);
    // select 返回以后，rdset里面就是本次的就绪集合
    if (FD_ISSET(STDIN_FILENO, &rdset)) {
      // stdin就绪
      memset(buf, 0, sizeof(buf));
      ssize_t sret = read(STDIN_FILENO, buf, sizeof(buf));
      if (sret == 0) {
        write(fdw, "nishigehaoren", 13);
        break;
      }
      write(fdw, buf, strlen(buf));
    }
    if (FD_ISSET(fdr, &rdset)) {
      // fdr就绪
      memset(buf, 0, sizeof(buf));
      ssize_t sret = read(fdr, buf, sizeof(buf));
      if (sret == 0) {
        printf("Hehe!\n");
        break;
      }
      printf("buf=%s\n", buf);
    }
  }
  close(fdr);
  close(fdw);
  return 0;
}
