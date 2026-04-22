#define _CRT_SECURE_NO_WARNINGS

#include "List.h"
#include<stdio.h>
#include<stdlib.h>

int main() {
	List* list = create_list();//创建空链表
	if (list == NULL) {
		printf("create_list failed in main.\n");
		exit(1);
	}
	//SAMSUNG
	add_behind_head(list, 'A');
	add_behind_head(list, 'S');
	add_behind_head(list, 'U');
	add_behind_head(list, 'N');
	add_node(list, 2, 'M');
	add_node(list, 1, 'S');
	add_node(list, list->size, 'G');
	//delete_node(list, 'N');
	Node* p = list->head;
	for (int i = 0; i < list->size; i++) {
		printf("%c\n", p->val);
		p = p->next;
	}
	int num = 2;
	Node* q = find_by_index(list, num);
	printf("find_by_index(list, %d) = %c\n", num, q->val);//数组下标格式
	//destroy_list(list);
	return 0;
}
