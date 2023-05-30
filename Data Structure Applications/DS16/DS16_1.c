#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 100

typedef struct element {
	int key;
} element;

typedef struct node* treePointer;
typedef struct node {
	element data;
	treePointer leftchild, rightchild;
};
treePointer treeRoot;

int searchList[MAX_ELEMENTS];
int n = 0;

treePointer modifiedSearch(treePointer tree, int k) {
	treePointer temp = tree;
	while (tree) {
		temp = tree;
		if (k < tree->data.key)
			tree = tree->leftchild;
		else if (k > tree->data.key)
			tree = tree->rightchild;
		else
			return NULL;
	}
	return temp;
}

void insert(treePointer* node, int k) {
	treePointer ptr, temp = modifiedSearch(*node, k);
	if (temp || !(*node)) {
		ptr = (treePointer)malloc(sizeof(*ptr));
		ptr->data.key = k;
		ptr->leftchild = NULL; ptr->rightchild = NULL;
		if (*node) {
			if (k < temp->data.key)
				temp->leftchild = ptr;
			else
				temp->rightchild = ptr;
		}
		else
			*node = ptr;
	}
}

void init() {
	int x;
	FILE* fp1 = fopen("input1.txt", "r");
	if (fp1 != NULL) {
		while (1) {
			if (feof(fp1))
				break;
			fscanf(fp1, "%d", &x);
			insert(&treeRoot, x);
		}
	}

	FILE* fp2 = fopen("input2.txt", "r");
	if (fp2 != NULL) {
		while (1) {
			if (feof(fp2))
				break;
			fscanf(fp2, "%d", &searchList[n]);
			n++;
		}
	}
	fclose(fp1); fclose(fp2);
}

void inorder(treePointer tree) {
	if (tree) {
		inorder(tree->leftchild);
		printf("%d ", tree->data.key);
		inorder(tree->rightchild);
	}
}

void preorder(treePointer tree) {
	if (tree) {
		printf("%d ", tree->data.key);
		preorder(tree->leftchild);
		preorder(tree->rightchild);
	}
}

void postorder(treePointer tree) {
	if (tree) {
		postorder(tree->leftchild);
		postorder(tree->rightchild);
		printf("%d ", tree->data.key);
	}
}

element* search(treePointer root, int k) {
	if (!root)
		return NULL;
	if (k == root->data.key)
		return &(root->data);
	if (k < root->data.key)
		return search(root->leftchild, k);

	return search(root->rightchild, k);
}


int main() {
	element* check;
	int i;

	init();
	printf("Preorder : ");
	preorder(treeRoot);
	printf("\n");

	printf("Inorder : ");
	inorder(treeRoot);
	printf("\n");

	printf("Postorder : ");
	postorder(treeRoot);
	printf("\n");

	printf("Search : ");
	for (i = 0; i < n; i++) {
		check = search(treeRoot, searchList[i]);
		if (check == NULL)
			printf("0 ");
		else
			printf("1 ");
	}
	printf("\n");
	return 0;
}


