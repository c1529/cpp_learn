#include <49func.h>
// 实现多个客户端连接一个服务器 一人发多人消息 聊天室
typedef struct conn_s{
    int netfd;
    int isalive;
} conn_t;
int main(int argc, char *argv[])
{
    ARGS_CHECK(argc,3);
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in addr;//服务端地址
    addr.sin_family=AF_INET;
    addr.sin_port=htons(atoi(argv[2]));
    addr.sin_addr.s_addr=inet_addr(argv[1]);
    int reuse=1;
    int ret = setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
    ERROR_CHECK(ret,-1,"setsocketopt");
    ret = bind(sockfd,(struct sockaddr *)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"bind");
    listen(sockfd,100);
    char buf[4096];

    conn_t clientArr[10];//保存所有连接客户端的信息    
    int curidx=0;//保存下一个连接客户端的下标

    int epfd = epoll_create(1);
    struct epoll_event event;
    event.data.fd = sockfd;
    event.events=EPOLLIN;// sockfd accept 对应的也是读行为
    epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&event);
    time_t curtime;

    while(1){
        struct epoll_event readySet[1024];
        int readyNum = epoll_wait(epfd,readySet,1024,1000);//等待最多1000ms
        for(int i=0;i<readyNum;i++){
            if(readySet[i].data.fd==sockfd){
                struct sockaddr_in clientAddr;
                socklen_t clientAddrSize=sizeof(clientAddr);
                int netfd=accept(sockfd,(struct sockaddr *)&clientAddr,&clientAddrSize);
                printf("netfd = %d\n",netfd);
                printf("client ip =%s,port = %d\n",inet_ntoa(clientAddr.sin_addr),ntohs(clientAddr.sin_port));
                clientArr[curidx].netfd=netfd;
                clientArr[curidx].isalive=1;
                event.data.fd=netfd;
                event.events=EPOLLIN;
                epoll_ctl(epfd,EPOLL_CTL_ADD,netfd,&event);
                curidx++;
            }
            else{
                ssize_t sret = recv(readySet[i].data.fd,buf,sizeof(buf),0);
                for(int j=0;j<curidx;j++){
                    if(clientArr[j].isalive==0||clientArr[j].netfd==readySet[j].data.fd){
                        continue;
                    }
                    send(clientArr[j].netfd,buf,strlen(buf),0);
                }
            }
        }}
    close(sockfd);
    return 0;
}

