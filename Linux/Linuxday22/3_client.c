#include <49func.h>

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
    fd_set rdset;
    char buf[2096]={0};
    while(1){
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(sockfd,&rdset);
        select(sockfd+1,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&rdset)){
            //发送消息
            bzero(buf,sizeof(buf));//效果跟memset一样
            ssize_t sret = read(STDIN_FILENO,buf,sizeof(buf));
            if(sret==0){
                send(sockfd,"lezi",4,0);
                break;
            }
            send(sockfd,buf,sret,0);
        }
        if(FD_ISSET(sockfd,&rdset)){//接收消息
            bzero(buf,sizeof(buf));
            ssize_t sret = recv(sockfd,buf,sizeof(buf),0);
            if (sret==0){
                printf("hehe");
                break;
            }
            printf("sret = %ld, buf = %s\n",sret,buf);
        }
    }
    close(sockfd);
    return 0;
}

