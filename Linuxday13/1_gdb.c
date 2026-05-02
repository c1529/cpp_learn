#include "49func.h"
int main() {
  DIR *dirp = opendir(".");
  struct dirent *direntp;
  while ((direntp = readdir(dirp)) != NULL) {
    printf("%s\n", direntp->d_name);
  }
  //继续读目录会报错
  direntp = readdir(dirp);
  printf("%s\n", direntp->d_name);
  return 0;
}
