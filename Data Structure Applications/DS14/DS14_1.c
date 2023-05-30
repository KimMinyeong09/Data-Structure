#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 100
#include <stdio.h>
#include <stdlib.h>

int treeArray[MAX_SIZE] = { 0 };
int num = 1;

typedef struct node* treePointer;
typedef struct node {
	int data;
	treePointer leftChild, rightChild;
};
treePointer treeRoot;
treePointer que[MAX_SIZE] = { 0 };
int front = -1; int rear = -1;

void initTree(int data) {
	treePointer New;
	New = (treePointer*)malloc(sizeof(struct node));
	treeRoot = New;
	treeRoot->data = data;
	treeRoot->rightChild = NULL;
	treeRoot->leftChild = NULL;
}

void makeArray() {
	FILE* f = fopen("input.txt", "r");
	int x;
	treeArray[0] = NULL;

	while (!feof(f)) {
		fscanf(f, "%d", &x);
		if (x == -1) {
			treeArray[num++] = NULL;
		}
		else {
			treeArray[num++] = x;
		}
	}
	fclose(f);
}

void levelOrder(int n){
	int i;
	for (i = 1; i < n; i++) {
		if (treeArray[i] != NULL)
			printf("%d ", treeArray[i]);
	}	
}

treePointer createNode(int data) {
	treePointer temp;
	temp = (treePointer*)malloc(sizeof(struct node));
	temp->data = data;
	temp->leftChild = NULL;
	temp->rightChild = NULL;
	return temp;
}

void appendLeft(treePointer parent, treePointer temp) {
	if (temp->data) {
		parent->leftChild = temp;
		rear++;
		que[rear] = temp;
		if (front < 0) {
			front = 0;
		}
	}
}

void appendRight(treePointer parent, treePointer temp) {
	if (temp->data) {
		parent->rightChild = temp;
		rear++;
		que[rear] = temp;
		if (front < 0) {
			front = 0;
		}
	}
}

void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->leftChild);
		printf("%d ", ptr->data);
		inorder(ptr->rightChild);
	}
}

void preorder(treePointer ptr) {
	if (ptr) {
		printf("%d ", ptr->data);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}

void postorder(treePointer ptr) {
	if (ptr) {
		postorder(ptr->leftChild);
		postorder(ptr->rightChild);
		printf("%d ", ptr->data);
	}
}

int main() {
	int i = 1, j;
	treePointer temp;
	makeArray();
	printf("Level Order: ");
	levelOrder(num);
	initTree(treeArray[i]);

	temp = treeRoot;

	for (j = 0; j < num; j++) {
		que[j] = NULL;
	}

	while (i <= (num / 2)) {
		appendLeft(temp, createNode(treeArray[i * 2]));
		appendRight(temp, createNode(treeArray[i * 2 + 1]));
		temp = (treePointer*)malloc(sizeof(struct node));
		temp = que[front];
		front++;
		i++;
	}

	printf("\nPreorder: ");
	preorder(treeRoot);
	printf("\nInorder: ");
	inorder(treeRoot);
	printf("\nPostorder: ");
	postorder(treeRoot);

	return 0;
}