#include "49func.h"
int main() {
  printf("uid = %d\neuid=%d\n", getuid(), geteuid());
  return 0;
}
