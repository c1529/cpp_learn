#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 10
typedef char* K;//key
typedef char* V;//value
typedef struct node {
	K key;
	V val;
	struct node* next;
} Node;
typedef struct {
	Node* table[N];
} HashMap;
//API
HashMap* hashmap_create();
void hashmap_destroy(HashMap* map);

V hashmap_put(HashMap* map, K key, V val);//添加
V hashmap_get(HashMap* map, K key);//查找
void hashmap_delete(HashMap* map, K key);//删除
