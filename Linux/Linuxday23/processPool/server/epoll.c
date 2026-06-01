//封装epoll的增加监听和移除监听
#include"head.h"
int epollAdd(int epfd,int fd){
    struct epoll_event event;
    event.events=EPOLLIN;
    event.data.fd=fd;
    int ret = epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&event);
    ERROR_CHECK(ret,-1,"epollAdd");
}
int epollDel(int epfd,int fd){
    int ret = epoll_ctl(epfd,EPOLL_CTL_DEL,fd,NULL);
    ERROR_CHECK(ret,-1,"epollDel");
    return 0;
}
