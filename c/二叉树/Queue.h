#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define N 10
typedef struct tree_node* E;
typedef struct {
    E elements[N];
    int front;
    int rear;
    int size;
}Queue;
//API
Queue* queue_create();
void queue_destroy(Queue* q);
void queue_push(Queue* q, E val);
E queue_pop(Queue* q);
E queue_peek(Queue* q);
bool queue_empty(Queue* q);
bool queue_full(Queue* q);