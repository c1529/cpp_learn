#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>

#define SIZE(a) (sizeof(a)/sizeof(a[0]))
void print_stu_info(struct student_s* s);
typedef struct student_s {
    int number;
    char name[25];
    char gender;
    //female male
    int chinese;
    int math;
    int english;
}
Student;

int main(int argc, char* argv[]) {
    struct student_s s1 = {1,"liuyifei",'f',100,100,100};
    Student s2 = {2,"libai",'m',77,99,88};
    print_stu_info(&s1);
    print_stu_info(&s2);
    return 0;
}

void print_stu_info(struct student_s* s) {
    //传入地址的原因主要是防止结构体被改变
    printf("%d %s %c %d %d %d\n",
        (*s).number,
        (*s).name,
        (*s).gender,
        (*s).chinese,
        (*s).math,
        (*s).english);
    printf("%d %s %c %d %d %d\n",//效果一样，不过更推荐下一种  简洁明了
        s->number,
        s->name,
        s->gender,
        s->chinese,
        s->math,
        s->english);
}
