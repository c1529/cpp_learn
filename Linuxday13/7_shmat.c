#include "49func.h"
int main() {
  int shmid = shmget(0x1234, 4096, IPC_CREAT | 0600);
  ERROR_CHECK(shmid, -1, "shmget");
  printf("shmid = %d\n", shmid);
  char *p = (char *)shmat(shmid, NULL, 0);
  p[0] = 'H';
  p[1] = 'i';
  shmdt(p);
  return 0;
}
