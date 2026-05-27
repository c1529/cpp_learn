#include <49func.h>

int main(int argc, char *argv[])
{
    // ./1_server 192.168.182.129 1234
    ARGS_CHECK(argc,3);    
    // 1.使用socket
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    // 2.建立bind
    struct sockaddr_in addr;//服务端的地址
    addr.sin_family = AF_INET;//ipv4类型
    addr.sin_port=htons(atoi(argv[2]));//端口号
    addr.sin_addr.s_addr=inet_addr(argv[1]);//ip地址
    int ret = bind(sockfd,(struct sockaddr *)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"bind");
    // 3.客户端connect之前需要listen监听
    listen(sockfd,100);
    // 4.accept函数
    struct sockaddr_in clientAddr;
    socklen_t clientAddrSize=sizeof(clientAddr);//必须初始化
    int new_sockfd = accept(sockfd,(struct sockaddr *)&clientAddr,&clientAddrSize);
    ERROR_CHECK(new_sockfd,"-1","accept");
    printf("new_sockfd = %d\n",new_sockfd);
    printf("client ip = %s, port = %d\n",inet_ntoa(clientAddr.sin_addr),ntohs(clientAddr.sin_port));
    char buf[2096]={0};
    ssize_t sret = recv(new_sockfd,buf,sizeof(buf),0);
    printf("sret = %ld, buf = %s\n",sret,buf);
    return 0;
}

