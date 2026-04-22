#include"49func.h"
int main(){
    int fdr = open("1.pipe",O_RDONLY);
    char buf[1024]={0};
    read(fdr,buf,sizeof(buf));
    printf("buf = %s",buf);
    close(fdr);
    return 0;
}
