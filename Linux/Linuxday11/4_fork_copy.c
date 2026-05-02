#include "49func.h"
int global = 1;
//子进程的变量修改不影响父进程
//子进程和父进程相互独立
int main() {
  int stack = 2;
  int *pHeap = (int *)malloc(sizeof(int));
  *pHeap = 3;
  if (fork() == 0) {
    // 子进程
    global += 3;
    stack += 3;
    *pHeap += 3;
    printf("i am child,global = %d, stack = %d, heap = %d\n", global, stack,
           *pHeap);
  } else {
    // 父进程
    sleep(2);
    printf("i am parent,global = %d, stack = %d, heap = %d\n", global, stack,
           *pHeap);
  }
  printf("i am end,global = %d, stack = %d, heap = %d\n", global, stack,
         *pHeap);
  return 0;
}
