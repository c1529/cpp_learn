#define _CRT_SECURE_NO_WARNINGS
#define N 100
#include<string.h>

void seperate(char* str);
void substitute_space(char* str);

int main() {
    //第一题
    char str[N]="h1ell2o3";
    seperate(str);
    puts(str);
    //第二题
    char str1[N] = "hello world goggle!";
    substitute_space(str1);
    puts(str1);
    return 0;
}

void seperate(char* str) {
    //将数字和字母分割开
    int number = 0, letter = 0;
    char str_number[N];
    char str_letter[N];
    char* p = str;

    while (*p != '\0') {

        if ((*p) >= 48 && (*p) <= 57) {
            str_number[number++] = *p;
            p++;
        }
        else {
            str_letter[letter++] = *p;
            p++;
        }
    }
    str_number[number] = '\0';
    str_letter[letter] = '\0';
    strcpy(str, str_number);
    // 先复制数字
    strcat(str, str_letter);
    // 再拼接字母
}

void substitute_space(char* str) {
    char temp[N];
    char* p = str;
    int i = 0;

    while (*p != '\0') {

        if (*p == ' ') {
            temp[i++] = '%';
            temp[i++] = '0';
            temp[i++] = '2';
            temp[i++] = '0';
        }
        else {
            temp[i++] = *p;
        }
        p++;
    }
    temp[i] = '\0';
    strcpy(str, temp);
}
