#include "49func.h"
int main() {
  if (fork() == 0) {
    printf("child:pid = %d,pgid = %d\n", getpid(), getpgid(0));
    setpgid(0, 0);
    printf("stepgid child:pid = %d,pgid = %d\n", getpid(), getpgid(0));
  } else {
    printf("parent:pid = %d,pgid = %d\n", getpid(), getpgid(0));
    wait(NULL);
  }
  return 0;
}
