#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct node* treePointer;
typedef struct node {
	char data;
	treePointer leftChild, rightChild;
}node;

node A1 = { 'A',NULL,NULL };
node A2 = { 'B', NULL,NULL };
node A3 = { '/',&A1,&A2 };
node A4 = { 'C',NULL,NULL };
node A5 = { '*', &A3,&A4 };
node A6 = { 'D', NULL,NULL };
node A7 = { '*' ,&A5,&A6 };
node A8 = { 'E' ,NULL,NULL };
node A9 = { '+' ,&A7,&A8 };
node* root = &A9;

void inorder(treePointer ptr){
	if (ptr) {
		inorder(ptr->leftChild);
		printf("%c", ptr->data);
		inorder(ptr->rightChild);
	}
}

void preorder(treePointer ptr){
	if (ptr) {
		printf("%c", ptr->data);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}

void postorder(treePointer ptr){
	if (ptr) {
		postorder(ptr->leftChild);
		postorder(ptr->rightChild);
		printf("%c", ptr->data);
	}
}


int main() {
	printf("Preorder : ");
	preorder(root);
	printf("\n");
	printf("Inorder : ");
	inorder(root);
	printf("\n");
	printf("Postorder : ");
	postorder(root);
	printf("\n");

	return 0;
}