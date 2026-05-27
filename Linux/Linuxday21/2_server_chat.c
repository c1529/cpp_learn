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
    int reuse=1;//SO_REUSEADDR属性的参数
                // setsockopt设置属性
                // TCP主动关闭连接后，端口会进入TIME_WAIT状态，默认1-2min内不能重新绑定
                // 这里使用这个setsockopt函数，程序刚推出就能立刻重启绑定同一个端口
    int ret=setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
    ERROR_CHECK(ret,-1,"setstockopt");
    ret = bind(sockfd,(struct sockaddr *)&addr,sizeof(addr));
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
    fd_set rdset;
    char buf[2096]={0};
    while(1){
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(new_sockfd,&rdset);
        select(new_sockfd+1,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&rdset)){
            //发送消息
            bzero(buf,sizeof(buf));//效果跟memset一样
            ssize_t sret = read(STDIN_FILENO,buf,sizeof(buf));
            if(sret==0){
                send(new_sockfd,"nishihaoren",11,0);
                break;
            }
            send(new_sockfd,buf,sret,0);
        }
        if(FD_ISSET(new_sockfd,&rdset)){//接收消息
            bzero(buf,sizeof(buf));
            ssize_t sret = recv(new_sockfd,buf,sizeof(buf),0);
            if(sret==0){
                printf("hehe");
                break;
            }
            printf("sret = %ld, buf = %s\n",sret,buf);
        }
    }
    close(new_sockfd);
    close(sockfd);
    return 0;
}

