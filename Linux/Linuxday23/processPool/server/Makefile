SRCS:=main.c worker.c tcpInit.c epoll.c sendfd.c transFile.c
OBJS:=$(SRCS:%.c=%.o)
server:$(OBJS)
	gcc $^ -o $@ -lpthread
%.o:%.c
	gcc -c $^ -o $@ -g
clean:
	$(RM) server $(OBJS)
