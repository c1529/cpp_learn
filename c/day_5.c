#include<stdio.h>
#define SIZE(arr) (sizeof(arr)/sizeof(arr[0]))
void swap(int* pa, int* pb) {
	int temp = *pa;  // 取出 pa 指向的值
	*pa = *pb;       // 将 pb 指向的值赋给 pa 指向的位置
	*pb = temp;      // 将原值赋给 pb 指向的位置
}
void find_min_max(const int arr[], int n, int* pmin, int* pmax) {
	*pmin = arr[0];
	*pmax = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] < *pmin) {
			*pmin = arr[i];
		}
		else if (arr[i] > *pmax) {
			*pmax = arr[i];
		}
	}
}
int main() {
	int a = 3, b = 4;
	//printf("a=%d,b=%d\n",a,b);
	//swap(&a, &b);
	//printf("a=%d,b=%d\n", a, b);
	const int* p;// pointer to const(常量指针)：不能通过指针p修改指针指向的对象
	p = &a;
	int* const q = &a;
	*q = 100;//指针变量    不能修改指针变量的值（也就是不能修改地址）
	printf("*q=%d\n", *q);
	int nums[6] = { 10,4,7,3,2,1 };
	printf("数组长度是 %d\n", (int)SIZE(nums));
	int max = nums[0];
	int min = nums[0];
	find_min_max(nums, SIZE(nums), &min, &max);
	printf("最小值是：%d\n最大值是：%d\n", min, max);
	return 0;
}
