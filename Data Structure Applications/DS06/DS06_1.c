#define _CRT_SECURE_NO_WARNINGS
#define MAX_TERM 1001
#define MAX_COL 1001
#include <stdio.h>
#include <stdlib.h>

int non_zero = 0;

typedef struct {
	int col;
	int row;
	int value;
}term;
term a[MAX_TERM];
term b[MAX_TERM];

int possibleAdd(int r1, int r2, int c1, int c2) {
	if (r1 == r2 && c1 == c2) {
		return 1;
	}
	else
		return 0;
}

void matrix_3Tuple(term a[], int** list, int r, int c) {
	int i, j;
	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++) {
			if (list[i][j] != 0) {
				++non_zero;
				a[non_zero].row = i;
				a[non_zero].col = j;
				a[non_zero].value = list[i][j];
			}
		}
	}


}

void fastTranspose(term a[], term b[]) {
	int rowTerms[MAX_COL], startingPos[MAX_COL];
	int i, j, numCols = a[0].col, numTerms = a[0].value;
	b[0].row = numCols;
	b[0].col = a[0].row;
	b[0].value = numTerms;
	if (numTerms > 0) {
		for (i = 0; i < numCols; i++) {
			rowTerms[i] = 0;
		}
		for (i = 1; i <= numTerms; i++) {
			rowTerms[a[i].col]++;
		}
		startingPos[0] = 1;
		for (i = 1; i < numCols; i++) {
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
		}
		for (i = 1; i <= numTerms; i++) {
			j = startingPos[a[i].col]++;
			b[j].row = a[i].col;
			b[j].col = a[i].row;
			b[j].value = a[i].value;
		}
	}
}

int main() {
	int temp1, temp2, sum, i, j;
	int maxRow1, maxCol1, maxRow2, maxCol2;
	int** matrixResult;
	FILE* mat1 = fopen("mat1.txt", "r");
	FILE* mat2 = fopen("mat2.txt", "r");

	fscanf(mat1, "%d", &maxRow1);
	fscanf(mat1, "%d", &maxCol1);
	fscanf(mat2, "%d", &maxRow2);
	fscanf(mat2, "%d", &maxCol2);
	
	if (possibleAdd(maxRow1, maxRow2, maxCol1, maxCol2)) {
		matrixResult = (int**) malloc(sizeof(int*) * maxRow1);
		for (i = 0; i < maxRow1; i++) {
			matrixResult[i] = malloc(sizeof(int) * maxCol1);
		}

		for (i = 0; i < maxRow1; i++) {
			for (j = 0; j < maxCol1; j++) {
				fscanf(mat1, "%d", &temp1);
				fscanf(mat2, "%d", &temp2);
				sum = temp1 + temp2;
				matrixResult[i][j] = sum;
				
			}
		}

		printf("Matrix Addition:\n");
		matrix_3Tuple(a, matrixResult, maxRow1, maxCol1);
		a[0].row = maxRow1;
		a[0].col = maxCol1;
		a[0].value = non_zero;
		for (i = 0; i <= non_zero; i++) {
			printf("%2d %2d %2d\n", a[i].row, a[i].col, a[i].value);
		}

		printf("Transpose Matrix:\n");
		fastTranspose(a, b);
		for (i = 0; i <= non_zero; i++) {
			printf("%2d %2d %2d\n", b[i].row, b[i].col, b[i].value);
		}

		for (int i = 0; i < maxRow1; i++) {
			free(matrixResult[i]);
		}
		free(matrixResult);

	}
	else
		printf("행렬의 계산이 불가능합니다.");
	
	fclose(mat1);
	fclose(mat2);

	return 0;
}