#include "49func.h"
int main() {
  printf("hello\n");
  fork();
  printf("world\n");
  sleep(20);
  return 0;
}
