#include "Stack.h"
void stack_push(Node** pstack, int val) {
	Node* new_node = malloc(sizeof(Node));
	if (new_node == NULL) {
		printf("malloc failed in stack_push.\n");
		exit(1);
	}
	new_node->val = val;
	new_node->next = *pstack;
	//改变stack的指向
	*pstack = new_node;
}
int stack_pop(Node** pstack) {
	if (stack_empty(*pstack)) {
		printf("Your stack is empty\n");
		exit(1);
	}
	Node* removenode = *pstack;
	(*pstack) = removenode->next;
	int res = removenode->val;
	free(removenode);
	return res;
}
int stack_peek(Node* stack) {
	if (stack == NULL) {
		printf("Your stack is empty\n");
		exit(1);
	}
	else {
		return stack->val;
	}
}
bool stack_empty(Node* stack) {
	return stack == NULL;
}
