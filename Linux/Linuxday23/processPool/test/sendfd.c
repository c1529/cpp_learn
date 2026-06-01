#include<49func.h>
int sendfd(int sockfd,int fdtosend){
    struct msghdr hdr;
    bzero(&hdr,sizeof(hdr));//不可省略
    //消息的正文
    char buf[]="hello";
    struct iovec iov[1];
    iov[0].iov_base=buf;
    iov[0].iov_len=5;
    hdr.msg_iov=iov;
    hdr.msg_iovlen=1;
    //消息的控制字段
    //堆空间存放变长结构体
    struct cmsghdr * pcmsghdr;
    pcmsghdr = (struct cmsghdr *)calloc(1,CMSG_LEN(sizeof(int)));
    pcmsghdr->cmsg_len=CMSG_LEN(sizeof(int));
    pcmsghdr->cmsg_level=SOL_SOCKET;
    pcmsghdr->cmsg_type = SCM_RIGHTS;//说明控制字符是文件描述符
    *(int *)CMSG_DATA(pcmsghdr)=fdtosend;// pcmsghdr找到data的首地址，把void * 转化成 int * ,再解引用赋值
    hdr.msg_control=pcmsghdr;
    hdr.msg_controllen=CMSG_LEN(sizeof(int));
    // sendmsg发送正文
    int ret = sendmsg(sockfd,&hdr,0);
}
int recvfd(int sockfd,int *pfdtorecv){
    struct msghdr hdr;
    bzero(&hdr,sizeof(hdr));//不可省略
    //消息的正文
    char buf[6]={0};
    struct iovec iov[1];
    iov[0].iov_base=buf;
    iov[0].iov_len=5;
    hdr.msg_iov=iov;
    hdr.msg_iovlen=1;
    //消息的控制字段
    //堆空间存放变长结构体
    struct cmsghdr * pcmsghdr;
    pcmsghdr = (struct cmsghdr *)calloc(1,CMSG_LEN(sizeof(int)));
    pcmsghdr->cmsg_len=CMSG_LEN(sizeof(int));
    pcmsghdr->cmsg_level=SOL_SOCKET;
    pcmsghdr->cmsg_type = SCM_RIGHTS;//说明控制字符是文件描述符
    // recvmsg 接收正文
    hdr.msg_control=pcmsghdr;
    hdr.msg_controllen=CMSG_LEN(sizeof(int));
    recvmsg(sockfd,&hdr,0);
    printf("buf = %s\n",buf);
    *pfdtorecv=*(int *)CMSG_DATA(pcmsghdr);
    printf("fdtorecv = %d\n",*pfdtorecv);
}
