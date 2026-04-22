#include "49func.h"
int main(int argc, char *argv[]) {
  // ./trans2 1.pipe
  int fdr = open(argv[1], O_RDONLY);
  ERROR_CHECK(fdr, -1, "open fdr");
  char buf[1024] = {0};
  // 接收文件名字
  read(fdr, buf, sizeof(buf));
  char filepath[4096] = {0};
  mkdir("./strage", 0777);
  sprintf(filepath, "%s/%s", "./strage", buf);
  // 新建文件
  int fdw = open(filepath, O_WRONLY | O_CREAT, 0666);
  ERROR_CHECK(fdw, -1, "open fdw");
  // 接收文件内容
  memset(buf, 0, sizeof(buf));
  ssize_t ret = read(fdr, buf, sizeof(buf));
  printf("ret = %ld.\n", ret);
  write(fdw, buf, strlen(buf));
  close(fdw);
  close(fdr);
  return 0;
}
