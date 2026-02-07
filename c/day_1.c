#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
void bar(void) {
	printf("bar begin\n");
	exit(123);//直接退出
	printf("bar end\n");
}
void swap(int *a, int *b) {//传递的是地址,直接修改内存中的数值
	int temp = *a;
	*a = *b;
	*b = temp;
}
void foo(void) {//局部静态变量会保留函数上一次的值
	static i = 0;
	printf("%p:%d\n", &i, i++);
	foo();
}
int main() {
	/*foo();*/
	printf("mian begin\n");
	bar();
	printf("main end\n");
	return 0;
}
