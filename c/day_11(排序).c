#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define SWAP(arr,i,j){        \
    int tmp = arr[i];\
arr[i]=arr[j];\
arr[j]=tmp;\
}
#define N 100
#define SIZE(a) (sizeof(a)/sizeof(a[0]))
void insertion_sort(int arr[], int n);
void shell_sort(int arr[], int n);
void merge_sort(int arr[], int n);
void printf_array(int arr[], int n);
void quick_sort(int arr[], int n);
void heap_sort(int arr[], int n);
int main() {
    int arr[] = {
        3,6,4,2,11,10,5
    }
    ;
    printf_array(arr, SIZE(arr));
    //insertion_sort(arr, SIZE(arr));
    //shell_sort(arr, SIZE(arr));
    //merge_sort(arr, SIZE(arr));
    quick_sort(arr, SIZE(arr));
    printf_array(arr, SIZE(arr));

    int arr1[] = { 9,1,2,5,7,4,8,6,3,0 };
    printf_array(arr1, SIZE(arr1));
    heap_sort(arr1, SIZE(arr1));
    printf_array(arr1, SIZE(arr1));
    return 0;
}

void insertion_sort(int arr[], int n) {
    //插入排序

    for (int i = 1; i < n; i++) {
        // i 表示要插入的元素的初始位置索引
        int value = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] >= value) {
            arr[j + 1] = arr[j];
            j--;
        }
        //此时 j =-1 || arr[j]<value
        arr[j + 1] = value;
    }
}
void shell_sort(int arr[], int n) {
    //希尔排序
    int gap = n / 2;

    while (gap) {
        //进行组间插入排序

        for (int i = gap; i < n; i++) {
            int value = arr[i];
            int j = i - gap;

            while (j >= 0 && arr[j] > value) {
                arr[j + gap] = arr[j];
                j = j - gap;
            }
            //j<0 || arr[j]<=value
            arr[j + gap] = value;
        }
        gap = gap / 2;
    }
}
void printf_array(int arr[], int n) {

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
void merge(int arr[], int left, int mid, int right) {
    int tmp[N];
    int i = left, j = left, k = mid + 1;
    while (j <= mid && k <= right) {
        if (arr[j] <= arr[k]) {
            tmp[i++] = arr[j++];
        }
        else {
            tmp[i++] = arr[k++];
        }
    }
    // j>mid || k>right
    while (j <= mid) {
        tmp[i++] = arr[j++];
    }
    while (k <= right) {
        tmp[i++] = arr[k++];
    }
    // 将合并后的数据从 tmp 复制回 arr
    for (int idx = left; idx <= right; idx++) {
        arr[idx] = tmp[idx];
    }
}
void merge_sort_helper(int arr[], int left, int right) {
    //边界条件
    if (left >= right) return;
    //递归公式
    int mid = left + (right - left) / 2;
    //对左半区间排序
    merge_sort_helper(arr, left, mid);
    //对右半区间排序
    merge_sort_helper(arr, mid + 1, right);
    //合并
    merge(arr, left, mid, right);
}
void merge_sort(int arr[], int n) {
    merge_sort_helper(arr, 0, n - 1);
}
int partition(int arr[], int left, int right) {
    int index = rand() % (right - left + 1) + left;
    int pivot = arr[index];
    SWAP(arr, index, right);

    int storeIndex = left;//下一个<=pivot的元素应该放置的位置
    for (int i = left; i < right; i++) {
        if (arr[i] <= pivot) {
            SWAP(arr, storeIndex, i);
            storeIndex++;
        }
    }
    SWAP(arr, storeIndex, right);
    return storeIndex;
}
void quick_sort_helper(int arr[], int left, int right) {
    //边界条件
    if (left >= right) return;
    //分区
    int index = partition(arr, left, right);
    //对左边区间排序
    quick_sort_helper(arr, left, index - 1);
    //对右边区间排序
    quick_sort_helper(arr, index + 1, right);
}
void quick_sort(int arr[], int n) {
    srand(time(NULL));
    quick_sort_helper(arr, 0, n - 1);
}
void heapify(int arr[], int i, int n) {
    while (i < n) {
        int maxIndex = i;
        int lchild = 2 * i + 1;
        int rchild = 2 * i + 2;
        if (lchild<n && arr[lchild]>arr[maxIndex]) {
            maxIndex = lchild;
        }
        if (rchild<n && arr[rchild]>arr[maxIndex]) {
            maxIndex = rchild;
        }
        if (maxIndex == i) break;
        SWAP(arr, i, maxIndex);
        i = maxIndex;
    }
}
void build_heap(int arr[], int n) {
    //从后往前构建大顶堆，找到第一个非叶子结点
    for (int i = (n - 2) / 2; i >= 0; i--) {
        heapify(arr, i, n);
    }
}
void heap_sort(int arr[], int n) {
    //构建大顶堆
    build_heap(arr, n);
    int len = n;//len表示无序区的长度
    while (len) {
        //交换堆顶元素和无序区的最后一个元素
        SWAP(arr, 0, len - 1);
        len--;
        heapify(arr, 0, len);//重新更新大顶堆
    }
}
