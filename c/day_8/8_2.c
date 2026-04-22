#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>

#define SIZE(a) (sizeof(a)/sizeof(a[0]))
typedef struct {
    int number;
    char name[25];
    int chinese;
    int math;
    int english;
}
Student;
void print_stu_info(Student* s);
void sort_students(Student* s[], int n);
int total_score(Student* s);
int compare(Student* s1, Student* s2);
void swap(Student* s[], int i, int j);

int main(int argc, char* argv[]) {
    Student students[5];
    for (int i = 0;

    i < SIZE(students); i++) {
        //输入学生基本信息
        scanf("%d%s%d%d%d", &students[i].number, &students[i].name, &students[i].chinese, &students[i].math, &students[i].english);
    }
    Student* pstudents[5] =  {
        students ,students + 1,students + 2,students + 3,students + 4
    }
    ;
    //结构体指针
    sort_students(pstudents, SIZE(pstudents));
    //排序
    for (int i = 0;

    i < SIZE(pstudents); i++) {
        //输出
        print_stu_info(pstudents[i]);
    }
    return 0;
}

int total_score(Student* s) {
    return s->chinese + s->english + s->math;
}

int compare(Student* s1, Student* s2) {
    //  <0:s1<s2
    //  =0:s1=s2
    //  >0:s1>s2
    return total_score(s1) - total_score(s2);
}

void print_stu_info(Student* s) {
    printf("%d %s %d %d %d\n",
    s->number, s->name, s->chinese, s->math, s->english);
}

void swap(Student* s[], int i, int j) {
    Student* temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

void sort_students(Student* s[], int n) {

    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;

        for (int j = i + 1; j < n; j++) {

            if (compare(s[j], s[minIdx]) < 0) {
                minIdx = j;
            }
        }
        swap(s, i, minIdx);
        //交换
    }
}
