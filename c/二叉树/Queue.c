#include "Queue.h"

Queue* queue_create() {
    return calloc(1, sizeof(Queue));
}

void queue_destroy(Queue* q) {
    free(q);
}

void queue_push(Queue* q, E val) {

    if (queue_full(q)) {
        printf("Your queue is full.\n");
        exit(1);
    }
    q->elements[q->rear] = val;
    q->rear = (q->rear + 1) % N;
    q->size++;
}

E queue_pop(Queue* q) {

    if (queue_empty(q)) {
        printf("Your queue is empty.\n");
        exit(1);
    }
    E res = q->elements[q->front];
    q->front = (q->front + 1) % N;
    q->size--;
    return res;
}

E queue_peek(Queue* q) {

    if (queue_empty(q)) {
        printf("Your queue is empty.\n");
        exit(1);
    }
    else {
        return q->elements[q->front];
    }
}

bool queue_empty(Queue* q) {
    return q->size == 0;
}

bool queue_full(Queue* q) {
    return q->size == N;
}