#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int number;
    char name[25];
    int chinese;
    int math;
    int english;
}
Student;
int cmp(const void* p1, const void* p2);
int total_score(Student* s);

int main() {
    Student students[5];

    for (int i = 0; i < 5; i++) {
        scanf("%d%s%d%d%d", &students[i].number, &students[i].name, &students[i].chinese, &students[i].math, &students[i].english);
    }
    Student* pstudents[5] = {
        students,students + 1,students + 2,students + 3,students + 4
    }
    ;
    qsort(pstudents, 5, sizeof(Student*), cmp);

    for (int i = 0; i < 5; i++) {
        printf("%d %s %d %d %d\n",
            pstudents[i]->number,
            pstudents[i]->name,
            pstudents[i]->chinese,
            pstudents[i]->math,
            pstudents[i]->english);
    }
    return 0;
}

int total_score(Student* s) {
    return s->chinese + s->math + s->english;
}

int cmp(const void* p1, const void* p2) {
    //返回正数：表示 a 排在 b 之后。
    //返回 0：表示 a 和 b 相等。
    //返回负数：表示 a 排在 b 之前。
    Student** s1 = p1;
    Student** s2 = p2;

    if (total_score(*s1) != total_score(*s2)) {
        return total_score(*s2) - total_score(*s1);
    }

    if ((*s1)->chinese != (*s2)->chinese) {
        return (*s2)->chinese - (*s1)->chinese;
    }

    if ((*s1)->math != (*s2)->math) {
        return (*s2)->math - (*s1)->math;
    }

    if ((*s1)->english != (*s2)->english) {
        return (*s2)->english - (*s1)->english;
    }
    return strcmp((*s1)->name, (*s2)->name);
}
