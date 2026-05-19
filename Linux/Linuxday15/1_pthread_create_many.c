#include "49func.h"
void *threadFunc(void *arg) {
  while (1) {
    sleep(1);
  }
}
int main() {
  long count = 0;
  while (1) {
    pthread_t tid;
    count++;
    int ret = pthread_create(&tid, NULL, threadFunc, NULL);
    //创建成功会返回0,失败会返回errnumber
    THREAD_ERROR_CHECK(ret, "pthread_create");
    if (ret != 0) {
      printf("count = %ld\n", count);
      break;
    }
  }
  return 0;
}
