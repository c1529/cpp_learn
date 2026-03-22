//判断一个数字是否是丑数 丑数是只包含质因子2，3，5的正整数
#include<stdio.h>
#include<stdbool.h>
bool isUglyNumber(long long n);
int main(){
    long long number = 12345;
    if(isUglyNumber(number)){
        printf("%lld is UglyNumber.\n",number);
    }else{
        printf("%lld is not UglyNUmber.\n",number);
    }
    return 0;
}
bool isUglyNumber(long long n){
    if(n<=1) return false;
    while(n%2==0){
        n/=2;
    }
    while(n%3==0){
        n/=3;
    }
    while(n%5==0){
        n/=5;
    }
    return true;
}
