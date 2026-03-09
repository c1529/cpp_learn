#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define N 10
typedef struct {
    int elements[N];
    int front;
    int rear;
    int size;
}Queue;
//API
Queue* queue_create();
void queue_destroy(Queue* q);
void queue_push(Queue* q, int val);
int queue_pop(Queue* q);
int queue_peek(Queue* q);
bool queue_empty(Queue* q);
bool queue_full(Queue* q);
