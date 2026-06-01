#include"head.h"
/*int transFile(int netfd){//这个版本是粘包问题
  send(netfd,"file1",5,0);
  int fd = open("file1",O_RDONLY);
  char buf[4096]={0};
  ssize_t sret = read(fd,buf,sizeof(buf));
  send(netfd,buf,sret,0);
  return 0;
  }*/
typedef struct train_s{
    int length;
    char data[4096];
}train_t;
/*
   int transFile(int netfd){//发送一个小文件  使用"小火车"协议
   train_t train={5,"file1"};
   send(netfd,&train,sizeof(train.length)+train.length,0);
   int fd = open("file1",O_RDONLY);
   ssize_t sret = read(fd,train.data,sizeof(train.data));
   train.length=sret;
   send(netfd,&train,sizeof(train.length)+train.length,0);
   return 0;
   }
   */
// 发送一个大文件
/*int transFile(int netfd){
    train_t train={5,"file1"};
    send(netfd,&train,sizeof(train.length)+train.length,MSG_NOSIGNAL);
    int fd = open("file1",O_RDONLY);
    while(1){
        bzero(&train,sizeof(train));
        ssize_t sret = read(fd,train.data,sizeof(train.data));
        if(sret==0){
            break;
        }
        train.length=sret;
        send(netfd,&train,sizeof(train.length)+train.length,MSG_NOSIGNAL);
        //printf("train.length = %d\n",train.length);
    }
    train.length=0;
    send(netfd,&train,sizeof(train.length),0);
    return 0;
}*/
/*
// 发送一个大文件 增加进度条功能
int transFile(int netfd){
    train_t train={5,"file1"};
    send(netfd,&train,sizeof(train.length)+train.length,MSG_NOSIGNAL);
    int fd = open("file1",O_RDONLY);
    struct stat statbuf;
    fstat(fd,&statbuf);
    printf("filesize = %ld\n",statbuf.st_size);
    train.length=sizeof(statbuf.st_size);
    memcpy(train.data,&statbuf.st_size,train.length);
    send(netfd,&train,sizeof(train.length)+train.length,MSG_NOSIGNAL);
    while(1){
        bzero(&train,sizeof(train));
        ssize_t sret = read(fd,train.data,sizeof(train.data));
        if(sret==0){
            break;
        }
        train.length=sret;
        send(netfd,&train,sizeof(train.length)+train.length,MSG_NOSIGNAL);
        //printf("train.length = %d\n",train.length);
    }
    train.length=0;
    send(netfd,&train,sizeof(train.length),0);
    return 0;
}
*/
// 使用mmap 减少一次用户态和内核态的拷贝
int transFile(int netfd){
    train_t train={5,"file1"};
    send(netfd,&train,sizeof(train.length)+train.length,MSG_NOSIGNAL);
    int fd = open("file1",O_RDWR);
    struct stat statbuf;
    fstat(fd,&statbuf);
    printf("filesize = %ld\n",statbuf.st_size);
    train.length=sizeof(statbuf.st_size);
    memcpy(train.data,&statbuf.st_size,train.length);
    send(netfd,&train,sizeof(train.length)+train.length,MSG_NOSIGNAL);
    off_t totalsize=0;
    //  mmap
    char *p=(char *)mmap(NULL,statbuf.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    ERROR_CHECK(p,MAP_FAILED,"mmap");
    //send
    while(totalsize<statbuf.st_size){
        if(statbuf.st_size - totalsize>(off_t)sizeof(train.data)){
            train.length=4096;
        }else{
            train.length=statbuf.st_size-totalsize;
        }
        send(netfd,&train.length,sizeof(train.length),MSG_NOSIGNAL);
        send(netfd,p+totalsize,train.length,MSG_NOSIGNAL);
        totalsize+=train.length;
    }
    train.length=0;
    send(netfd,&train.length,sizeof(train.length),MSG_NOSIGNAL);
    munmap(p,statbuf.st_size);
    return 0;
}

