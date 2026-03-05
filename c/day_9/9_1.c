#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#define SIZE(a) (sizeof(a)/sizeof(a[0]))
char* my_strcat(const char* s1, const char* s2);
int main() {
	char* str = my_strcat("Hello ", "World!!!!!");
	puts(str);
	return 0;
}

char* my_strcat(const char* s1, const char* s2) {
	char* result = malloc(strlen(s1) + strlen(s2) + 1);
	if (result == NULL) {
		printf("malloc failed in my_strcat!\n");
		exit(1);
	}
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}
