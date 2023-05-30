#define _CRT_SECURE_NO_WARNINGS
#define COMPARE(x,y)  (((x)<(y)) ? -1 : ((x)==(y)) ? 0 : 1)
#include <stdio.h>
#include <stdlib.h>

typedef struct polyNode* polyPointer;
typedef struct polyNode {
	int coef;
	int expon;
	polyPointer link;
};

polyPointer createNode(int tempCoef, int tempExpon) {
	polyPointer temp;
	temp = (polyPointer*)malloc(sizeof(polyPointer));
	temp->coef = tempCoef;
	temp->expon = tempExpon;
	temp->link = NULL;
	return temp;
}

polyPointer append(polyPointer head, polyPointer temp) {
	polyPointer nextNode = head;
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

void attach(int coefficient, int exponent, polyPointer* ptr) {
	polyPointer temp;
	temp = (polyPointer*)malloc(sizeof(polyPointer));
	temp->coef = coefficient;
	temp->expon = exponent;
	(*ptr)->link = temp;
	*ptr = temp;
}

polyPointer padd(polyPointer a, polyPointer b) {
	polyPointer c, rear, temp;
	int sum;
	rear = (polyPointer*)malloc(sizeof(polyPointer));
	c = rear;
	while (a && b) {
		switch (COMPARE(a->expon, b->expon)) {
		case -1:
			attach(b->coef, b->expon, &rear);
			b = b->link;
			break;
		case 0:
			sum = a->coef + b->coef;
			if (sum)
				attach(sum, a->expon, &rear);
			a = a->link;
			b = b->link;
			break;
		case 1:
			attach(a->coef, a->expon, &rear);
			a = a->link;
			break;
		}
	}
	for (; a; a = a->link)
		attach(a->coef, a->expon, &rear);
	for (; b; b = b->link)
		attach(b->coef, b->expon, &rear);
	rear->link = NULL;
	temp = c;
	c = c->link;
	free(temp);
	return c;
}

void printPoly(polyPointer head) {
	printf("%dx^%d", head->coef, head->expon);
	head = head->link;
	for (; head; head = head->link) {
		if (head->expon == 0)
			printf(" %+d", head->coef);
		else
			printf(" %+dx^%d", head->coef, head->expon);
	}
	printf("\n");
}

int main() {
	int num1, num2, i;
	int co, ex;
	polyPointer result;
	polyPointer a = (polyPointer*)malloc(sizeof(polyPointer));
	polyPointer b = (polyPointer*)malloc(sizeof(polyPointer));
	a = NULL; b = NULL;
	FILE* fp1 = fopen("a.txt", "r");
	FILE* fp2 = fopen("b.txt", "r");

	fscanf(fp1, "%d", &num1);
	fscanf(fp2, "%d", &num2);

	for (i = 0; i < num1; i++) {
		fscanf(fp1, "%d", &co);
		fscanf(fp1, "%d", &ex);
		a = append(a, createNode(co, ex));
	}

	for (i = 0; i < num2; i++) {
		fscanf(fp2, "%d", &co);
		fscanf(fp2, "%d", &ex);
		b = append(b, createNode(co, ex));
	}

	result = padd(a, b);
	printPoly(result);

	fclose(fp1);
	fclose(fp2);

	return 0;
}