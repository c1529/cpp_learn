#include"49func.h"
int main(){
    // stdin stdout stderr 都是FILE* 类型文件
    // fileno()函数是将FILE*类型文件准化成文件描述符fd
    printf("stdin fd is %d\n",fileno(stdin));
    printf("stdout fd is %d\n",fileno(stdout));
    printf("stderr fd is %d\n",fileno(stderr));
    return 0;
}
