#include <49func.h>
// 相对比2多实现一个断线重连机制
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
                // TCP主动关闭接后，端口会进入TIME_WAIT状态，默认1-2min内不能重新绑定
                // 这里使用这个setsockopt函数，程序刚推出就能立刻重启绑定同一个端口
    int ret=setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
    ERROR_CHECK(ret,-1,"setstockopt");
    ret = bind(sockfd,(struct sockaddr *)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"bind");
    // 3.客户端connect之前需要listen监听
    listen(sockfd,100);
    char buf[4096];
    fd_set rdset;//每次select传入的参数
    fd_set monitorset;//下次select的监听集合，复制到sdset中
    FD_ZERO(&monitorset);
    FD_SET(sockfd,&monitorset);
    int new_sockfd;
    while(1){
        memcpy(&rdset,&monitorset,sizeof(fd_set));//复制到rdset中
        select(100,&rdset,NULL,NULL,NULL);//select调用只会修改rdset,不修改monitorset
        if(FD_ISSET(sockfd,&rdset)){
            // 4.accept函数
            struct sockaddr_in clientAddr;
            socklen_t clientAddrSize=sizeof(clientAddr);//必须初始化
            new_sockfd = accept(sockfd,(struct sockaddr *)&clientAddr,&clientAddrSize);
            ERROR_CHECK(new_sockfd,"-1","accept");
            printf("new_sockfd = %d\n",new_sockfd);
            printf("client ip = %s, port = %d\n",inet_ntoa(clientAddr.sin_addr),ntohs(clientAddr.sin_port));
            //这个时候连接上了
            //我们希望服务器连接上只跟当前的保持连接
            //不希望跟其他客户建立连接
            FD_CLR(sockfd,&monitorset);
            FD_SET(STDIN_FILENO,&monitorset);
            FD_SET(new_sockfd,&monitorset);
        }
        if(FD_ISSET(STDIN_FILENO,&rdset)){
            //发送消息
            bzero(buf,sizeof(buf));//效果跟memset一样
            ssize_t sret = read(STDIN_FILENO,buf,sizeof(buf));
            if(sret==0){
                send(new_sockfd,"nishihaoren",11,0);
                FD_CLR(STDIN_FILENO,&monitorset);
                FD_CLR(new_sockfd,&monitorset);
                FD_SET(sockfd,&monitorset);//重新等待一个客户端连接
                close(new_sockfd);
                printf("你是一个好人。我主动断开连接\n");
            }
            send(new_sockfd,buf,sret,0);
        }
        if(FD_ISSET(new_sockfd,&rdset)){//接收消息
            bzero(buf,sizeof(buf));
            ssize_t sret = recv(new_sockfd,buf,sizeof(buf),0);
            if(sret==0){//对方断开连接
                FD_CLR(STDIN_FILENO,&monitorset);
                FD_CLR(new_sockfd,&monitorset);
                FD_SET(sockfd,&monitorset);//重新等待一个客户端连接
                close(new_sockfd);
                printf("你是一个坏人。你竟然主动断开连接\n");
            }
            printf("sret = %ld, buf = %s\n",sret,buf);
        }
    }
    close(new_sockfd);
    close(sockfd);
    return 0;
}

