#include "Stack.h"
int main() {
	Node* stack = NULL;
	for (int i = 0; i < 5; i++) {
		stack_push(&stack, i*i);
	}
	int num = stack_pop(&stack);
	printf("%d\n", num);
	printf("%d\n", stack_peek(stack));
	return 0;
}
