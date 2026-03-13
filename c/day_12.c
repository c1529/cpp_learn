#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define SIZE(a) (sizeof(a)/sizeof(a[0]))
int binary_search1(int arr[], int n, int key);
int binary_search2(int arr[], int n, int key);
int main() {
	int arr[] = { 1,2,4,6,8,9,10,11,14,15,18 };
	int index1 = binary_search1(arr, SIZE(arr), 10);
	printf("%d\n", index1);
	int index2 = binary_search2(arr, SIZE(arr), 10);
	printf("%d\n", index2);
	return 0;
}
//递归
int bsearch1(int arr[],int left,int right,int key) {
	if (left > right) return -1;
	int mid = left + (right - left) / 2;
	if (key < arr[mid]) {
		return bsearch1(arr, left, mid - 1, key);
	}
	else if (key > arr[mid]) {
		return bsearch1(arr, mid+1, right, key);
	}
	else {
		return mid;
	}
}
int binary_search1(int arr[], int n, int key) {
	return bsearch1(arr, 0, n - 1, key);
}
//循环
int binary_search2(int arr[], int n, int key) {
	int left = 0, right = n - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (key < arr[mid]) {
			right = mid - 1;
		}
		else if (key > arr[mid]) {
			left = mid + 1;
		}
		else {
			return mid;
		}
	}
	//left>right
	return -1;
}
