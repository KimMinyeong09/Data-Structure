#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
};
listPointer head, tail;

void InitList(listPointer ptr) {
	listPointer New;
	New = (listPointer*)malloc(sizeof(struct listNode));
	ptr = New;
	ptr = NULL;
}

void addNode(int data) {
	listPointer temp = (listPointer*)malloc(sizeof(listPointer));
	temp->data = data;
	if (head == NULL) {
		head = tail = temp;
		return;
	}
	tail->link = temp;
	temp->link = head;
	tail = temp;
}

void removeNode(listPointer temp) {
	listPointer prev = tail;
	listPointer seek = head;
	while (seek != tail) {
		if (seek == temp) {
			break;
		}
		prev = seek;
		seek = seek->link;
	}
	if (seek == tail && seek != temp) {
		return;
	}
	prev->link = seek->link;
	tail = prev;
	head = prev->link;
}

listPointer findNode(listPointer seek, int n) {
	int i;
	if (seek == NULL) {
		return NULL;
	}
	for (i = 1; i < n; i++)
		seek = seek->link;

	return seek;
}

int main() {
	int friends, rhyme, num;
	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%d %d", &friends, &rhyme);

	InitList(head); InitList(tail);

	for (num = 1; num <= friends; num++) {
		addNode(num);
	}

	for (num = 1; num < friends; num++) {
		removeNode(findNode(head, rhyme));
	}

	printf("input.txt\n");
	printf("%d %d\n",friends, rhyme);
	printf("Output\n");
	printf("%d", head->data);

	fclose(fp);
	return 0;
}