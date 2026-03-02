#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>

#define SIZE(a) (sizeof(a)/sizeof(a[0]))
void find_two_largest(int arr[], int n, int* largest, int* second_largest);

int main() {
    int largest, second_largest;
    int arr[] =  {
        3,6,4,1,99,5,7,8,23
    }
    ;
    find_two_largest(arr, SIZE(arr), &largest, &second_largest);
    printf("largest = %d ,second_largest = %d\n", largest, second_largest);
    return 0;
}

void find_two_largest(int arr[], int n, int* largest, int* second_largest) {
    //初始化
    *largest = arr[0] > arr[1] ? arr[0] : arr[1];
    *second_largest = arr[0] < arr[1] ? arr[0] : arr[1];

    for (int i = 2; i < n; i++) {

        if (arr[i] > *largest) {
            *second_largest = *largest;
            *largest = arr[i];
        }

        else if (arr[i] > *second_largest) {
            *second_largest = arr[i];
        }
    }
}
