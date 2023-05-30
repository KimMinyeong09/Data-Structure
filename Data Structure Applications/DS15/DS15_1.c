#define _CRT_SECURE_NO_WARNINGS
#define MAX_ELEMENTS 200
#define HEAP_FULL(n) (n == MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int key;
}element;
element heap[MAX_ELEMENTS];
int n = 0;

void push(element item, int* n) {
	int i;
	if (HEAP_FULL(*n)) {
		fprintf(stderr, "The heap is full.\n");
		exit(EXIT_FAILURE);
	}
	i = ++(*n);
	while ((i != 1) && (item.key > heap[i / 2].key)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}

element pop(int* n){ 
	int parent, child;
	element item, temp;
	if (HEAP_EMPTY(*n)) {
		fprintf(stderr, "The heap is empty\n");
		exit(EXIT_FAILURE);
	}
	item = heap[1]; 
	temp = heap[(*n)--];
	parent = 1;
	child = 2;
	while (child <= *n) {
		if ((child < *n) && (heap[child].key < heap[child + 1].key))
			child++;
		if (temp.key >= heap[child].key) break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;
}

void iterInorder() {
	int i = 1, data, count = 0;
	int top = -1;
	int stack[MAX_ELEMENTS];
	while (1) {
		while (i <= n) {
			stack[++top] = i;
			i *= 2;
		}
		data = stack[top];
		top--;

		printf("%d ", heap[data].key);
		count++;

		data = data * 2 + 1;
		if (data <= n) {
			i = data;
		}

		if (count >= n) {
			printf("\n");
			break;
		}
	}
}


void creatHeap() {
	FILE* fp = fopen("input.txt", "r");
	element temp;
	int data;

	while (1) {
		if (feof(fp))
			break;
		fscanf(fp, "%d", &data);
		temp.key = data;
		push(temp, &n);
	}
	fclose(fp);

}

void printLevel() {
	int i;
	for (i = 1; i <= n; i++) {
		printf("%d ", heap[i].key);
	}
	printf("\n");
}

int main() {
	creatHeap();
	printf("Level Order: ");
	printLevel();

	printf("Inorder:     ");
	iterInorder();

	pop(&n);
	printf("Level Order: ");
	printLevel();

	printf("Inorder:     ");
	iterInorder();

	pop(&n);
	printf("Level Order: ");
	printLevel();

	printf("Inorder:     ");
	iterInorder();

	return 0;
}