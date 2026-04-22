#include"49func.h"
int main(int argc,char* argv[]){
    // ./5_a.c 1.pipe 2.pipe
    ARGS_CHECK(argc,3);
    int fdr = open(argv[1],O_RDONLY);
    int fdw = open(argv[2],O_WRONLY);
    ERROR_CHECK(fdr,-1,"open in fdr");
    ERROR_CHECK(fdw,-1,"open in fdw");
    printf("chat is established.\n");
    close(fdr);
    close(fdw);
    return 0;
}



