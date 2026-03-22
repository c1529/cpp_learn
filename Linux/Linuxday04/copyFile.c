#include<stdio.h>
#include<stdlib.h>
int main(int argc,char* argv[]){
    if(argc!=3){
        fprintf(stderr,"Usage:./copyFile src dst\n");
        exit(1);
    }
    FILE* src_fp = fopen(argv[1],"rb");//src表示源头的意思
    if(src_fp==NULL){
        fprintf(stderr,"open %s failed\n",argv[1]);
        exit(1);
    }
    FILE* dst_fp = fopen(argv[2],"wb");
    if(dst_fp==NULL){
        fprintf(stderr,"open %s failed\n",argv[2]);
        fclose(src_fp);
        exit(1);
    }
    char buffer[1024];
    int n;
    // fread返回实际读取数据个数 每次读取之后文件的指针都会在上次结束之后的位置
    // fread(void *ptr,size_t size,size_t size_count,FILE *stream);
    // void *ptr用于存放从文件里读取的数据
    // size 单个数据的大小
    // count 最多读取的个数
    // FILE *stream 打开文件的指针
    while((n=fread(buffer,1,1024,src_fp))>0){
        fwrite(buffer,1,n,dst_fp);
    }
    //关闭文件
    fclose(src_fp);
    fclose(dst_fp);
    return 0;
}
