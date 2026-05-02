#include "49func.h"
// NUM 太大会导致数据出错，因为p[0]++不是原子操作
#define NUM 1000000
int main() {
  int shmid = shmget(IPC_PRIVATE, 4096, IPC_CREAT | 0600);
  ERROR_CHECK(shmid, -1, "shmget");
  int *p = (int *)shmat(shmid, NULL, 0); // 挂载共享内存
  p[0] = 0;
  if (fork() == 0) {
    // 子进程
    for (int i = 0; i < NUM; i++) {
      p[0]++;
    }
  } else {
    for (int i = 0; i < NUM; i++) {
      p[0]++;
    }
    wait(NULL);
    printf("p[0] = %d\n", p[0]);
  }
  return 0;
}
