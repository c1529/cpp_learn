#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
int main() {
	printf("%d\n", errno);//errno设置为0
	FILE* fp = fopen("no_exist.txt", "r");
	printf("%d\n", errno);
	printf("%s\n", strerror(errno));
	if (errno != 0) {
		perror("no_exist.txt");
	}
	return 0;
}
