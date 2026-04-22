#include<stdio.h>
#define SIZE(a) (sizeof(a)/sizeof(a[0]))
int findMin(int arr[],int n);
int main(){
  int arr[] = {4,5,7,8,9,10,2,3};
  int min = findMin(arr,SIZE(arr));
  printf("%d\n",arr[min]);
  return 0;
}
int findMin(int arr[],int n){
    int left =0,right=n-1;
    while(left<right){
        int mid = (left+right)/2;
        if(arr[mid]<arr[right]){
            right = mid;
        }else{
            left = mid+1;
        }
    }
    return left;
}
