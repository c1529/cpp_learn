#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
typedef struct node {
	int val;
	struct node* next;
} Node;
//API
//入栈和出栈都需要改变栈顶指针的值，所以传递二级指针
void stack_push(Node** pstack, int val);//入栈
int stack_pop(Node** pstack);//出栈
int stack_peek(Node* stack);//查看栈顶元素
bool stack_empty(Node* stack);//判空
