#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node *treePointer;
typedef struct node {
	int data;
	treePointer leftChild, rightChild;
};
treePointer root;

treePointer modifiedSearch(treePointer node, int k) {
	treePointer temp=node;
	while (node) {
		temp = node;
		if (node->data > k)
			node = node->leftChild;
		else if (node->data < k)
			node = node->rightChild;
		else
			return NULL;
	}
	return temp;
}

void insert(treePointer *node, int k) {
	treePointer ptr, temp = modifiedSearch(*node, k);
	if (temp || !(*node)) {
		ptr = (treePointer)malloc(sizeof(*ptr));
		ptr->data = k;
		ptr->leftChild = ptr->rightChild = NULL;
		if (*node) {
			if (k < temp->data)
				temp->leftChild = ptr;
			else
				temp->rightChild = ptr;
		}
		else
			*node = ptr;
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
	FILE*fp = fopen("input.txt", "r");
	root = (treePointer)malloc(sizeof(*root));
	root = NULL;
	int count = 0;
	int temp;
	while (1) {
		if (feof(fp))
			break;
		fscanf(fp, "%d", &temp);
		count++;
		insert(&root, temp);
	}
	//printf("%d\n", count);
	printf("Preorder: ");
	preorder(root);
	printf("\nInorder: ");
	inorder(root);
	printf("\nPostorder: ");
	postorder(root);
	printf("\nHeight: ");
	/*heigt ±¸ÇÏ±â*/

	fclose(fp);
	return 0;
}