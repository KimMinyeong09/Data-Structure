#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
};

listPointer createNode(int tempNum) {
	listPointer temp;
	temp = (listPointer*)malloc(sizeof(listPointer));
	temp->data = tempNum;
	temp->link = NULL;
	return temp;
}

listPointer append(listPointer head, listPointer temp) {
	listPointer nextNode = head;
	if (head == NULL) {
		head = temp;
		return head;
	}
	while (nextNode->link != NULL) {
		nextNode = nextNode->link;
	}
	nextNode->link = temp;
	return head;
}

listPointer concatenate(listPointer ptr1, listPointer ptr2) {
	listPointer temp;
	if (!ptr1) return ptr2;
	if (!ptr2) return ptr1;

	for (temp = ptr1; temp->link; temp = temp->link);
	temp->link = ptr2;
	return ptr1;
}

listPointer invert(listPointer lead) {
	listPointer middle, trail;
	middle = NULL;
	while (lead) {
		trail = middle;
		middle = lead;
		lead = lead->link;
		middle->link = trail;
	}
	return middle;
}

void printList(listPointer head) {
	for (; head; head = head->link) {
		printf("(%p, %d, %p) ", head, head->data, head->link);
	}
	printf("\n\n");
}

int main() {
	int x;
	listPointer first = (listPointer*)malloc(sizeof(listPointer));
	listPointer second = (listPointer*)malloc(sizeof(listPointer));
	listPointer con;
	listPointer inv;
	first = NULL;
	second = NULL;
	FILE* fp1 = fopen("input1.txt", "r");
	FILE* fp2 = fopen("input2.txt", "r");

	while (1) {
		if (feof(fp1))
			break;
		fscanf(fp1, "%d", &x);
		first = append(first, createNode(x));
	}

	while (1) {
		if (feof(fp2))
			break;
		fscanf(fp2, "%d", &x);
		second = append(second, createNode(x));
	}

	printf("First:\n");
	printList(first);
	printf("Second:\n");
	printList(second);

	con = concatenate(first, second);
	printf("Concatenate:\n");
	printList(con);

	inv = invert(con);
	printf("Invert:\n");
	printList(inv);

	fclose(fp1);
	fclose(fp2);
	return 0;
}