#include "49func.h"
int main() {
  DIR *dirp = opendir("."); // 打开当前文件
  struct dirent *direntp;
  while ((direntp = readdir(dirp)) != NULL) {
    printf("%s\n", direntp->d_name);
  }
  return 0;
}
