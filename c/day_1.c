#include<stdio.h>
#include<stdbool.h>
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
	foo();
	return 0;
}
