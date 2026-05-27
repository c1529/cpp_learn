#include <49func.h>
// 实现多个客户端连接一个服务器 一人发多人消息
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

    fd_set rdset;
    fd_set monitorset;
    FD_ZERO(&monitorset);
    FD_SET(sockfd,&monitorset);
    while(1){
        memcpy(&rdset,&monitorset,sizeof(fd_set));
        select(100,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(sockfd,&rdset)){
            struct sockaddr_in clientAddr;
            socklen_t clientAddrSize = sizeof(clientAddr);
            int netfd = accept(sockfd,(struct sockaddr *)&clientAddr,&clientAddrSize);
            printf("netfd = %d\n",netfd);
            printf("client ip = %s, port = %d\n",inet_ntoa(clientAddr.sin_addr),ntohs(clientAddr.sin_port));
            clientArr[curidx].netfd=netfd;
            clientArr[curidx].isalive=1;//1表示存活  0表示已经断开
            FD_SET(netfd,&monitorset);
            curidx++;
        }
        for(int i=0;i<curidx;i++){
            // 如果存活 并且已经就绪
            if(clientArr[i].isalive==1&&FD_ISSET(clientArr[i].netfd,&rdset)){
                //读取该客户端发送的消息，转发给其他客户端
                bzero(buf,sizeof(buf));
                ssize_t sret = recv(clientArr[i].netfd,buf,sizeof(buf),0);
                if (sret==0){
                    clientArr[i].isalive=0;
                    FD_CLR(clientArr[i].netfd,&monitorset);
                    close(clientArr[i].netfd);
                }
                for(int j=0;j<curidx;j++){
                    if(j==i||clientArr[j].isalive==0){
                        continue;//发送是自己或者目标已经关闭
                    }
                    send(clientArr[j].netfd,buf,strlen(buf),0);
                }
            }
        }
    }
    close(sockfd);
    return 0;
}

