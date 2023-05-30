#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int key;
}element;

element* stack;
int capacity = 1;
int top = -1;

void stackFull() {
	stack = (element*)realloc(stack, 2 * capacity * sizeof(*stack));
	capacity *= 2;
}

element pop() {
	return stack[top--];
}

void check() {
	int i;
	for (i = 0; i <= top; i++) {
		printf("%2d", stack[i].key);
	}
}

int main() {
	char command;
	int push, i;
	stack = (element*)malloc(sizeof(*stack));

	FILE* input = fopen("input.txt", "r");

	while (1) {
		fscanf(input, "%c", &command);
		if (feof(input)) break;

		if (command == 'I') {//pushStack
			fscanf(input, "%d", &push);
			if (top >= (capacity - 1)) {//Full
				stackFull();
				top++;
				stack[top].key = push;

			}
			else {//NotFull
				top++;
				stack[top].key = push;
			}
		}
		else if (command == 'D') {//popStack
			if (top < 0) {//Empty
				printf("ERROR::Stack is Empty\n");
			}
			else {//NotEmpty
				stack[top--];
			}
		}	
	}

	printf("Capacity: %d\n", capacity);
	printf("Stack:");
	check();

	free(stack);
	fclose(input);

	return 0;
}