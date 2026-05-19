#include<stdio.h>
#include<sys/select.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/time.h>
#include<dirent.h>
#include<fcntl.h>
#include<time.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/wait.h>
#include<syslog.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/time.h>
#define ARGS_CHECK(argc,num) {if(argc!=num){fprintf(stderr,"args error!\n");return -1;}}
#define ERROR_CHECK(ret,num,msg) {if(ret==num){perror(msg);return -1;}}
