#include "49func.h"
int main() {
  FILE *fp = popen("./hello", "r"); // 读取hello程序中的printf
  ERROR_CHECK(fp, NULL, "popen");
  char buf[1024] = {0};
  fread(buf, 1, sizeof(buf), fp);
  printf("buf = %s", buf);
  pclose(fp);
  return 0;
}
