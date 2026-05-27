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
    sleep(5);
    printf("sleep over\n");
    ssize_t sret = send(sockfd,"hello world!",12,0);
    printf("sret = %ld\n",sret);
    return 0;
}

