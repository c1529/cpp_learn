#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int main() {
    //打开文件
    char* filename = "The_Holy_Bible.txt";
    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error: open %s failed,\n", filename);
        exit(1);
    }
    char ch1;
    //复制文件  读写文件
    FILE* fp2 = fopen("bible.txt", "w");

    if (fp2 == NULL) {
        printf("Error: open %s failed,\n", "bible.txt");
        fclose(fp);
        exit(1);
    }

    while ((ch1 = fgetc(fp)) != EOF) {
        //EOF表示文件末尾
        fputc(ch1, fp2);
    }

    for (int i = 0; i < 100; i++) {
        //ch1不断读取  最后到文件末尾所以输出是空白
        ch1 = fgetc(fp);
        putchar(ch1);
    }
    //关闭文件
    fclose(fp);
    return 0;
}
