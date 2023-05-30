#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_DEGREE 1001
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

typedef struct {
	int degree;
	int coef[MAX_DEGREE];
}polynomial;

int LeadExp(polynomial poly) {
	return poly.degree;
}

int Coef(polynomial poly, int expon) {
	if (poly.degree >= expon)
		return poly.coef[expon];
	else
		return 0;
}

int IsZero(polynomial poly) {
	if (poly.degree == 0 && poly.coef[0] == 0)
		return 1;
	else
		return 0;
}

polynomial Attach(polynomial poly, int co, int expon) {
	poly.coef[expon] = co;
	return poly;
}

polynomial Remove(polynomial poly, int expon) {
	if (poly.degree >= expon) {
		poly.degree--;
		if (poly.degree<0) {
			poly.degree = 0;
		}
		poly.coef[expon] = 0;
		return poly;
	}
	else
		printf("ERROR\n");

}

int main() {
	polynomial A, B, D;
	int x, i, num1, num2, temp1, temp2, sum;
	FILE* a = fopen("a.txt", "r");
	FILE* b = fopen("b.txt", "r");

	D.degree = 0;
	D.coef[0] = 0;

	printf("a.txt\n");
	while (!feof(a)) {
		fscanf(a, "%d", &x);
		printf("%d ", x);
	}printf("\n");
	printf("b.txt\n");
	while (!feof(b)) {
		fscanf(b, "%d", &x);
		printf("%d ", x);
	}printf("\n");

	fseek(a, 0, SEEK_SET);
	fseek(b, 0, SEEK_SET);

	for (i = 0; i < 3; i++) {
		fscanf(a, "%d", &A.degree);
		fscanf(b, "%d", &B.degree);
	}

	for (i = 0; i <= A.degree; i++) {
		A.coef[i] = 0;
	}

	for (i = 0; i <= B.degree; i++) {
		B.coef[i] = 0;
	}

	fseek(a, 0, SEEK_SET);
	fseek(b, 0, SEEK_SET);

	fscanf(a, "%d", &num1);
	fscanf(b, "%d", &num2);

	for (i = 0; i < num1; i++) {
		fscanf(a, "%d", &temp1);
		fscanf(a, "%d", &temp2);
		A.coef[temp2] = temp1;
	}

	for (i = 0; i <= num2; i++) {
		fscanf(b, "%d", &temp1);
		fscanf(b, "%d", &temp2);
		B.coef[temp2] = temp1;
	}

	D.degree = ((A.degree) < (B.degree)) ? B.degree : A.degree;
	
	while (IsZero(A)==0 || IsZero(B)==0) {
		switch COMPARE(LeadExp(A), LeadExp(B)) {
		case -1: 
			D = Attach(D, Coef(B, LeadExp(B)), LeadExp(B));
			B = Remove(B, LeadExp(B));
			break; 
		case 0: 
			sum = Coef(A, LeadExp(A)) + Coef(B, LeadExp(B));
			D = Attach(D, sum, LeadExp(A));
			A = Remove(A, LeadExp(A));
			B = Remove(B, LeadExp(B));
			break;
		case 1: 
			D = Attach(D, Coef(A, LeadExp(A)), LeadExp(A));
			A = Remove(A, LeadExp(A));
			break; 
		}
	}

	printf("%dx^%d", D.coef[D.degree], D.degree);
	for (i = D.degree - 1; i >= 0; i--) {
		if (D.coef[i] != 0) {
			if (i != 0) {
				printf(" + %dx^%d", D.coef[i], i);
			}
			else {
				printf(" + %d", D.coef[i]);
			}
		}
	}

	fclose(a);
	fclose(b);

	return 0;
}