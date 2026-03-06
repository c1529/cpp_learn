#pragma once

typedef struct node {//结点信息
	char val;
	struct node* next;
} Node;

typedef struct {//存放整个链表信息
	Node* head;
	Node* tail;
	int size;
} List;

//API
List* create_list();
void destroy_list(List* list);

void add_before_head(List* list, char val);
void add_behind_head(List* list, char val);
void add_node(List* list, int index, char val);

void delete_node(List* list, int val);

Node* find_by_index(List* list, int index);
Node* search_for_value(List* list, int val);

