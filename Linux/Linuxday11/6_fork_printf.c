#include "49func.h"
int main() {
  fork();
  printf("A");
  fork();
  printf("A");
  return 0;
}
