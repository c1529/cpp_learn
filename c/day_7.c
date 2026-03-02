#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>

#define SIZE(a) (sizeof(a)/sizeof(a[0]))

int main() {
    /*
    //1.strcpy 和strncpy 复制字符串
    char str[10];
    strcpy(str, "hello");
    strcpy(str, "hello world!");
    //会报错。
    strncpy(str, "hello world!", SIZE(str) - 1);
    str[SIZE(str) - 1] = '\0';
    //补充末尾的0字符
    */
    /*
    //2.strlen 求字符串长度
    printf("%d", (int)strlen("abc"));
    //默认不算空字符
    */
    /*
    //3.strcat函数  string concatenate  拼接
    char s1[20] = "hello ";
    //strcat(s1, "world!");
    //弊端 不会检查数组是否会越界
    strncat(s1, "world!", SIZE(s1) - strlen("world!") - 1);
    puts(s1);
    */
    //4.strcmp(s1,s2)  is s1<s2?   相等就返回0  比较第一个字母的ASCLL大小，如果相等比较第二个...
    printf("%d", strcmp("ksd", "fg"));
    return 0;
}
