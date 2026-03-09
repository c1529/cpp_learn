#include "Queue.h"

int main() {
	Queue* q = queue_create();
	if (q == NULL) {
		printf("queue_create failed in main.\n");
	}
	q->size = 0,q->front=0,q->rear=0;//初始化
	queue_push(q, 1);
	queue_push(q, 2);
	queue_push(q, 3);
	queue_push(q, 4);
	while (!queue_empty(q)) {
		int data = queue_peek(q);
		printf("%d\n", data);
		queue_pop(q);
	}
	if (queue_empty(q)) {
		printf("queue is empty in main.\n");
	}
	return 0;
}
