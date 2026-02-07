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
long long fib(int n) {
	if (n == 0 || n == 1) return n;
	return fib(n - 1) + fib(n - 2);
}
long long fib_2(int n) {//动态规划
	if (n == 0 || n == 1) return n;
	int a = 0, b = 1;
	int c = a + b;//初始化i=1的情况
	for (int i = 2; i <= n; i++) {
		c = a + b;
		a = b;
		b = c;
	}
	return b;
}
void hanoi(int n);
int main() {
	/*foo();*/
	//printf("mian begin\n");
	//bar();
	//printf("main end\n");
	//printf("%lld\n", fib(10));
	//printf("%lld\n", fib_2(10));
	hanoi(3);
	return 0;
}
void hanoi_helper(int n,char start,char middle,char target) {//具体实现代码
	//边界条件 n==1
	if (n == 1) {
		printf("%c --> %c\n", start, target);
		return;
	}
	//递归公式
	//1. 将上面n-1个盘子移动到中间的杆子上面
	hanoi_helper(n - 1, start, target, middle);
	//2. 把最大的盘子移动到目标杆子上
	printf("%c --> %c\n", start, target);
	//3. 把中间的杆子上n-1个盘子移动到目标杆子上 
	hanoi_helper(n - 1,middle, start, target);
}
void hanoi(int n) {//汉诺塔   S(n)=2^n-1
	long long steps = (1 << n) - 1;
	printf("total steps:%lld\n", steps);
	hanoi_helper(n, 'A', 'B', 'C');//委托 外包
}
