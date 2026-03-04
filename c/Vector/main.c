#define _CRT_SECURE_NO_WARNINGS
#include "Vector.h"
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#define SIZE(a) (sizeof(a)/sizeof(a[0]))

int main() {
	Vector* v = creaet_vector();
	if (!v) {
		printf("create_vector failed.\n");
		exit(1);
	}

	for (int i = 0; i < 100; i++) {
		push_back(v,i * i);
	}
	int* p = v->elements;
	for (int i = 0; i < 100; i++) {
		printf("%d\n",*p++);
	}
	destroy_vector(v);

	return 0;
}
