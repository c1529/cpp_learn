#include <49func.h>
typedef struct train_s{
    int length;
    char data[4096];
}train_t;
/*
   int recvn(int sockfd,void *buf,int length){//使用这个recvn也可以代替MSG_WAITALL
   int total=0;
   char *p=(char *)buf;
   while(total<length){
   ssize_t sret = recv(sockfd,p+total,length-total,0);
   total+=sret;
   }
   return 0;
   }
   */
int recvFile(int sockfd){
    train_t train;
    bzero(&train,sizeof(train));
    recv(sockfd,&train.length,sizeof(train.length),MSG_WAITALL);//先接受文件名字长度
    recv(sockfd,train.data,train.length,MSG_WAITALL);//接收文件名字
    int fd = open(train.data,O_WRONLY|O_TRUNC|O_CREAT,0666);
    off_t filesize;
    recv(sockfd,&train.length,sizeof(train.length),MSG_WAITALL);
    recv(sockfd,train.data,train.length,MSG_WAITALL);
    memcpy(&filesize,train.data,sizeof(off_t));
    printf("filesize = %ld\n",filesize);
    off_t cursize=0;
    off_t lastsize=0;
    while(1){
        bzero(&train,sizeof(train));
        recv(sockfd,&train.length,sizeof(train.length),MSG_WAITALL);
        if(train.length==0){
            printf("传送已经结束");
            break;
        }
        recv(sockfd,train.data,train.length,MSG_WAITALL);
        write(fd,train.data,train.length);
        cursize+=train.length;
        if((double)cursize-lastsize>filesize/1000.0){
            printf("%5.2lf%%\r",100.0*cursize/filesize);
            fflush(stdout);
            lastsize=cursize;
        }
        //printf("%5.2lf%%\n",100.0*cursize/filesize);


    }
    return 0;
}
int main(int argc, char *argv[])
{
    // ./1_cilent 192.168.182.129 1234
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    //客户端需要填写服务端的地址
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(atoi(argv[2]));//端口号
    addr.sin_addr.s_addr=inet_addr(argv[1]);//ip
    int ret = connect(sockfd,(struct sockaddr *)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"connect");
    //sleep(5);
    //printf("sleep over\n");
    recvFile(sockfd);
    return 0;
}

