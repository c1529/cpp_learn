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
    //用指针数组，每个元素只是一个指针（通常 8 字节），
    //排序时 qsort 交换的是指针，而不是整个结构体。这样排序的移动成本大大降低，尤其当数据量较大时性能提升明显

    //如果直接写 Student pstudents[5]，那只是另一个结构体数组，你需要手动从 students 复制数据（比如用循环或 memcpy），然后对它排序。
    // 这样既增加了复制开销，又多占用了内存，且复制后的数据与原始数据是独立的，修改一方不会影响另一方，可能不符合需求。
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
