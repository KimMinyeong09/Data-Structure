#define _CRT_SECURE_NO_WARNINGS
#define MAX_RECORD 10000
#include <stdio.h>
#include <stdlib.h>

typedef struct element{
	int key1;
	int key2;
}element;
element record[MAX_RECORD];
int recordTotal = 0;
int left = 0;
int right = 0;

void init() {
	int i, j, k;
	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &recordTotal);
	for (k = 0; k < recordTotal; k++) {
		fscanf(fp, "%d %d", &i, &j);
		record[k].key1 = i;
		record[k].key2 = j;
	}

	fclose(fp);
}

void SWAP(element* a, element* b) {
	element temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void print() {
	int i;
	for (i = 0; i < recordTotal; i++) {
		printf("%d %d\n", record[i].key1, record[i].key2);
	}
}

void quickSortKey1(element a[], int left, int right) {
	int pivot, i, j;
	if (left < right) {
		i = left;
		j = right + 1;
		pivot = a[left].key1;
		do {
			do i++; while (a[i].key1 < pivot);
			do j--; while (a[j].key1 > pivot);
			if (i < j)SWAP(&a[i], &a[j]);
		} while (i < j);
		SWAP(&a[left], &a[j]);
		quickSortKey1(a, left, j - 1);
		quickSortKey1(a, j + 1, right);
	}
}

void quickSortKey2(element a[], int left, int right) {
	int pivot, i, j;
	if (left < right) {
		i = left;
		j = right + 1;
		pivot = a[left].key2;
		do {
			do i++; while (a[i].key2 < pivot);
			do j--; while (a[j].key2 > pivot);
			if (i < j)SWAP(&a[i], &a[j]);
		} while (i < j);
		SWAP(&a[left], &a[j]);
		quickSortKey2(a, left, j - 1);
		quickSortKey2(a, j + 1, right);
	}
}



int main() {
	init();
	printf("Key: K1\n");
	quickSortKey1(record, 0, recordTotal - 1);
	print();

	init();
	printf("Key: K2\n");
	quickSortKey2(record, 0, recordTotal - 1);
	print();

	return 0;
}