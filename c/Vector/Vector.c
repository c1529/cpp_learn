#define _CRT_SECURE_NO_WARNINGS
#include "Vector.h"
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#define DEFAULT_CAPACITY 8
#define THRESHOLD 1024
#define SIZE(a) (sizeof(a)/sizeof(a[0]))
Vector* creaet_vector() {
	Vector* v = malloc(sizeof(Vector));
	if (v == NULL) {
		return NULL;
	}
	v->elements = malloc(DEFAULT_CAPACITY * sizeof(int));
	if (v->elements == NULL) {
		free(v);
		return NULL;
	}
	v->capacity = DEFAULT_CAPACITY;
	v->size = 0;
	return v;
}

void destroy_vector(Vector* v) {
	free(v->elements);
	free(v);
}

void grow_capacity(Vector* v) {
	if (v->capacity <= THRESHOLD) {
		v->capacity = v->capacity * 2;
	}
	else {
		v->capacity += (v->capacity >> 1);   //变成1.5倍
	}
	int* result = realloc(v->elements, v->capacity * sizeof(int));
	if (result == NULL) {
		printf("realloc failed in grow_capacity.\n");
		exit(1);
	}
	v->elements = result;//指向新的内存空间
}

void push_back(Vector* v, int val) {
	if (v->size == v->capacity) {
		grow_capacity(v);
	}
	v->elements[v->size++] = val;
}
