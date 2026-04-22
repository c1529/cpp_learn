# 自动找到当前目录下所有 .c 文件
SRCS := $(wildcard *.c)

# 把 .c 文件名变成可执行文件名（比如 test.c → test）
TARGETS := $(patsubst %.c,%,$(SRCS))

# 默认编译所有
all: $(TARGETS)

# 编译规则：xxx.c 自动生成 xxx
%: %.c
	gcc $< -o $@

# 清理所有可执行文件
clean:
	rm -f $(TARGETS)
