#include"49func.h"
int main(int argc,char* argv[]){
    ARGS_CHECK(argc,2);
    FILE* fp = fopen(argv[1],"a+");
    ERROR_CHECK(fp,NULL,"fopen");
    char* buf = "\n123321\n";
    fwrite(buf,1,strlen(buf),fp);
    fclose(fp);
}
