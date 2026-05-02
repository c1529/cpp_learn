#include "49func.h"
int main() {
  if (fork() == 0) {
    while(1);
  } else {
    int wstatus;
    wait(&wstatus);
    if (WIFEXITED(wstatus)) {
      printf("exit normally!exit code = %d\n", WEXITSTATUS(wstatus));
    } else if (WIFSIGNALED(wstatus)) {
      printf("exit abnormally!terminal signal = %d\n", WTERMSIG(wstatus));
    }
  }
  return 0;
}
