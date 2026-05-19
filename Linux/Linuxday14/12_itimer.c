#include "49func.h"
void sigFunc(int signum) {
  printf("signum = %d\n", signum);
  time_t now = time(NULL);
  printf("currtime = %s\n", ctime(&now));
}
int main() {
  sigFunc(0);
  struct itimerval itimer;
  itimer.it_value.tv_sec = 3;
  itimer.it_value.tv_usec = 0;
  itimer.it_interval.tv_sec = 1;
  itimer.it_interval.tv_usec = 0;
  signal(SIGPROF, sigFunc);
  setitimer(ITIMER_PROF, &itimer, NULL);
  while (1)
    ;
  return 0;
}
