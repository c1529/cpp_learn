#include <stdio.h>

#define SIZE(a) sizeof(a)/sizeof(a[0])
int read_line(char str[], int n);

int main() {
    //char str[10];
    ////匹配规则：忽略前置的空白字符，读取字符存入字符数组，知道遇到空白字符结束，并且会在后面添加\0
    ////弊端：1.不能读取空白字符
    //scanf_s("%9s", str, 10);
    // 或者写 10
    //puts(str);
    //自己写一个read_line函数
    char str[10];
    int n = read_line(str, SIZE(str) - 1);
    printf("%d", n);
    return 0;
}

int read_line(char str[], int n) {
    //不会跳过前置空白字符，并且在第一个换行符（不保存到字符串里面）处停止读取，
    // 如果输入的字符串太长，那么就要忽略额外的字符
    char ch;
    int i = 0;

    while ((ch = getchar()) != '\n') {

        if (i < n) {
            //这个if语句保证了字符不会超出指定的n值
            str[i++] = ch;
        }
    }
    str[i] = '\0';
    puts(str);
    return i;
}
