#define _CRT_SECURE_NO_WARNINGS

#include "List.h"
#include<stdio.h>
#include<stdlib.h>



List* create_list() {
	// 创建空链表
	return calloc(1, sizeof(List));
}
void destroy_list(List* list) {
	//if (list->size == 0) {
	//	return;
	//}
	//遍历链表
	Node* curr = list->head;
	while (curr!=NULL) {
		Node* next = curr->next;
		printf("%c",curr->val);
		free(curr);
		curr = next;
	}
	//释放list
	free(list);
}

void add_before_head(List* list, char val) {//头插法
	//创建结点
	Node* new_node = malloc(sizeof(Node));
	if (new_node == NULL) {
		printf("malloc failed in add_before_head.\n");
		exit(1);
	}
	//初始化结点
	new_node->val = val;
	//插入节点
	new_node->next = list->head;
	if (list->size == 0) {
		list->tail = list->head;
	}
	list->head = new_node;
	list->size++;
}
void add_behind_head(List* list, char val) {//尾插法
	//创建结点
	Node* new_node = malloc(sizeof(Node));
	if (new_node == NULL) {
		printf("malloc failed in add_behind_head.\n");
		exit(1);
	}
	//初始化结点
	new_node->val = val;
	//插入节点
	if (list->size == 0) {
		list->head = new_node;
		list->tail = new_node;
	}
	else {
		list->tail->next = new_node;
		list->tail = new_node;
	}
	list->size++;
}
void add_node(List* list, int index, char val) {//按照索引
	if (index<0 || index>list->size) {
		printf("Your index is err.\n");
		return;
	}
	//插入节点
	Node* p = list->head;
	if (index == 1) {
		add_before_head(list, val);
		return;
	}
	if (index == list->size) {
		add_behind_head(list, val);
		return;
	}
	//创建结点
	Node* new_node = malloc(sizeof(Node));
	if (new_node == NULL) {
		printf("malloc failed in add_node.\n");
		exit(1);
	}
	//初始化结点
	new_node->val = val;
	Node* curr = list->head;
	int num = index - 2;
	while (num--) {
		curr = curr->next;
	}
	new_node->next = curr->next;
	curr->next = new_node;
	list->size++;
	return;
}

void delete_node(List* list, int val) {//删除链表中第一个跟val相等的结点
	if (list->size == 0) {
		printf("The length of your list is 0.\n");
		return;
	}
	Node* curr = list->head;
	Node* pre = NULL;
	while (curr) {
		if (curr->val == val) {
			//TODO 删除curr
			if (pre == NULL) {
				//说明要删除第一个结点
				list->head = curr->next;
				if (list->size == 1) {//说明仅有的一个结点删除了
					list->tail = NULL;
				}
				free(curr);
			}
			else {
				pre->next = curr->next;
				if (curr->next == NULL) {
					list->tail = pre;
				}
				free(curr);
			}
			list->size--;
			return;
		}
		pre = curr;
		curr = curr->next;
	}
}

Node* find_by_index(List* list, int index) {
	if (index<0 || index>=list->size) {//按照数组的来
		printf("Your index is err.\n");
		return NULL;
	}
	int num = index;
	Node* curr = list->head;
	while (num--) {
		curr = curr->next;
	}
	return curr;
}
Node* search_for_value(List* list, int val) {//在链表中找到第一个与val相等的结点
	Node* curr = list->head;
	while (curr) {
		if (curr->val == val) {
			return curr;
		}
		curr = curr->next;
	}
	return NULL;
}
