# 进程池



todo:

1. 在两个进程之间共享文件描述符 sendmsg和recvmsg
2. CMSG_LEN和CMSG_DATA
3. 粘包问题（TCP是一个流式协议），send和recv不是一一对应的
4. 比较两个文件是否一样 md5sum函数
5. send的第四个参数，MSG_NOSIGNAL可以防止客户端终止导致服务端无限运行的状态（避免SIGPIPE）
6. “半包问题”，发送的文件太大导致客户端收到的文件不对，可以使用recv的第四个参数，MSG_WAITALL
7. 用mmap实现数据的拷贝，可以减少一次内核态和用户态之间的拷贝（也可以用sendfile）
8. 异步拉起同步





















