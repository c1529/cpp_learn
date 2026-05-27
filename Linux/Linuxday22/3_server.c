#include <49func.h>
//epoll使用
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
    int netfd = accept(sockfd,(struct sockaddr *)&clientAddr,&clientAddrSize);
    ERROR_CHECK(netfd,"-1","accept");
    printf("netfd = %d\n",netfd);
    printf("client ip = %s, port = %d\n",inet_ntoa(clientAddr.sin_addr),ntohs(clientAddr.sin_port));
    //fd_set rdset;
    int epfd = epoll_create(1);
    struct epoll_event event;
    event.data.fd=STDIN_FILENO;
    event.events=EPOLLIN;
    epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    event.data.fd=netfd;
    event.events=EPOLLIN;
    epoll_ctl(epfd,EPOLL_CTL_ADD,netfd,&event);
    char buf[4096]={0};
    while(1){
        struct epoll_event readySet[2];
        int readyNum = epoll_wait(epfd,readySet,2,-1);// -1表示永久等待
        for(int i=0;i<readyNum;i++){
            if(readySet[i].data.fd==STDIN_FILENO){
                bzero(buf,sizeof(buf));
                ssize_t sret = read(STDIN_FILENO,buf,sizeof(buf));
                if(sret==0){
                    send(netfd,"nishigehaoren",13,0);
                    goto end;//跳出多重循环 break只能跳出单重
                }
                send(netfd,buf,strlen(buf),0);
            }else if(readySet[i].data.fd==netfd){
                bzero(buf,sizeof(buf));
                ssize_t sret=recv(netfd,buf,sizeof(buf),0);
                if(sret==0){
                    printf("hehe\n");
                    goto end;
                }
                printf("buf = %s\n",buf);
            }
        }
    }
end:
    close(netfd);
    close(sockfd);
    return 0;
}

