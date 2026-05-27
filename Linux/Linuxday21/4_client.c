#include <49func.h>
//UDP通信的服务端
int main(int argc, char *argv[])
{
    // ./4_server 192.128.182.129 1234
    ARGS_CHECK(argc,3);
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);// udp SOCK_DGRAM
    struct sockaddr_in serverAddr;
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr=inet_addr(argv[1]);
    //客户端先sendto
    sendto(sockfd,"zaima",5,0,
           (struct sockaddr *)&serverAddr,sizeof(serverAddr));
    sleep(5);
    char buf[4096]={0};
    recvfrom(sockfd,buf,sizeof(buf),0,NULL,NULL);
    printf("buf = %s\n",buf);//对面发送两次 但是只接受第一次的
    close(sockfd);
    return 0;
}

