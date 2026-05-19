#include "49func.h"
int main(int argc, char *argv[]) {
  // ./9_kill pid
  ARGS_CHECK(argc, 2);
  kill(atoi(argv[1]), 9);
  return 0;
}
