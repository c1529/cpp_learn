#include "49func.h"
int main() {
  int shmid = shmget(0x1234, 4096, IPC_CREAT | 0600);
  ERROR_CHECK(shmid, -1, "shmget");
  char *p = (char *)shmat(shmid, NULL, 0);
  printf("p = %s\n", p);
  return 0;
}
