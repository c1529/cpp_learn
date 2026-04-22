#include "49func.h"
int main(int argc, char *argv[]) {
  // ./trans1 file1 1.pipe
  ARGS_CHECK(argc, 3);
  int fdw = open(argv[2], O_WRONLY); // 写入管道
  ERROR_CHECK(fdw, -1, "open fdw");
  int fdr = open(argv[1], O_RDONLY); // 读取文件
  char buf[1024] = {0};
  // 1. 发文件名字
  write(fdw, argv[1], strlen(argv[1]));
  // 先获取文件里面的内容到buf中
  ssize_t ret = read(fdr, buf, sizeof(buf));
  // 写文件内容
  write(fdw, buf, ret);
  close(fdw);
  close(fdr);
  return 0;
}
