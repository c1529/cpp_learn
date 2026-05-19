#include "49func.h"
void cleanup1(void *arg) {
  // arg 直接传入p1
  printf("cleanup1\n");
  free(arg);
}
void cleanup2(void *arg) {
  printf("cleanup2\n");
  free(arg);
}
void cleanup3(void *arg) {
  // 直接传入fd3地址
  int *pfd3 = (int *)arg;
  printf("cleanup3\n");
  close(*pfd3);
}
void *threadFunc(void *arg){
//申请资源后马上压栈
void *p1=malloc(4);
pthread_cleanup_push(cleanup1,p1);
void *p2=malloc(4);
pthread_cleanup_push(cleanup2,p2);
int fd3 = open("file1",O_RDWR);
pthread_cleanup_push(cleanup3,&fd3);
// 把原来清理资源的行为替换弹栈
//close(fd3)
pthread_cleanup_pop(1);
//free(p2);
pthread_cleanup_pop(1);
//free(p1);
pthread_cleanup_pop(1);
}
int main() {
  pthread_t tid;
  pthread_create(&tid, NULL, threadFunc, NULL);
  void *ret;
  pthread_join(tid, &ret);
  printf("ret = %ld\n", (long)ret);
  return 0;
}
