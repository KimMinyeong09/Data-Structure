#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 100
#define TRUE 1
#define FALSE 0
#include <stdio.h>
#include <stdlib.h>

typedef struct stack* stackPointer;
typedef struct stack {
	int data;
	stackPointer link;
};
stackPointer seq[MAX_SIZE];
int out[MAX_SIZE];

stackPointer x, y, top;

void push(int index, int item) {
	stackPointer temp;
	temp = (stackPointer*)malloc(sizeof(struct stack));
	temp->data = item;
	temp->link = seq[index];
	seq[index] = temp;
}

int main() {
	int objectNum, pairNum;
	int i, j, n;

	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &objectNum);
	fscanf(fp, "%d", &pairNum);

	for (n = 0; n < objectNum; n++) {
		seq[n] = NULL;
		out[n] = TRUE;
	}

	while (1) {
		if (feof(fp))
			break;
		fscanf(fp, "%d %d", &i, &j);
		push(i, j);
		push(j, i);
	}

	for (i = 0; i < objectNum; i++) {
		if (out[i]) {
			printf("\nNew Class: %d ", i);
			out[i] = FALSE;

			x = seq[i];
			while (1) {
				while (x) {
					j = x->data;
					if (out[j]) {
						printf("%d ", j);
						out[j] = FALSE;
						y = x->link;
						x->link = top;
						top = x;
						x = y;
					}
					else 
						x = x->link;
				}
				if (!top)
					break;
				x = seq[top->data];
				top = top->link;
			}
		}
	}

	fclose(fp);
	return 0;
}