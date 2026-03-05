#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>

typedef struct node_s {
    //定义结点类型
    int data;
    struct node_s* next;
}
Node;
Node* addNode(Node* list, int data);
//添加结点

int main() {
    Node* list = NULL;

    for (int i = 0; i < 5; i++) {
        list = addNode(list, i * i);
    }
    Node* p = list;

    for (int i = 0; i < 5; i++) {
        printf("%d\n", p->data);
        p = p->next;
    }
    return 0;
}

Node* addNode(Node* list, int data) {
    //创建结点
    Node* node = malloc(sizeof(Node));

    if (node == NULL) {
        printf("malloc is failed in addNode.\n");
        exit(1);
    }
    node->data = data;
    node->next = list;
    list = node;
    return list;
}
