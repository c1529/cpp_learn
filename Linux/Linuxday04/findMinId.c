#include<stdio.h>
#define SIZE(a) (sizeof(a)/sizeof(a[0]))
#define SWAP(arr,i,j){   \
    int temp = arr[i];   \
    arr[i]=arr[j];       \
    arr[j]=temp;       \
}
int findMinId(int arr[],int n);
int main(){
    int arr[]={9,5,2,7,0,3,1,6,8,11};
    int MinId = findMinId(arr,SIZE(arr));
    printf("MINID = %d\n",MinId);
    return 0;
}
int findMinId(int arr[],int n){
    int left =0,right=n-1;
    while(left<right){
        int pivot = left+(right-left>>1);
        int storeIdx = left;
        for(int i=left;i<=right;i++){
            if(arr[i]<=pivot){
                SWAP(arr,storeIdx,i);
                storeIdx++;
            }
        }
        if(storeIdx==pivot+1){
            left = storeIdx;
        }else{
            right = storeIdx-1;
        }
    }
    return (arr[left]==left)?left+1:left;
}
