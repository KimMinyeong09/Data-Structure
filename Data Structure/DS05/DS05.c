#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 10000
#include <stdio.h>
#include <stdlib.h>

typedef struct element {
	int key;
}element;

element array[MAX_SIZE];
int total = 0;

void init() {
	int i, temp;
	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &total);
	for (i = 1; i <= total; i++) {
		fscanf(fp, "%d", &temp);
		array[i].key = temp;
	}
	fclose(fp);
}

void adjust(element a[], int root, int n) {
	int child, rootkey;
	element temp;
	temp = a[root];
	rootkey = a[root].key;
	child = 2 * root;
	while (child <= n) {
		if ((child < n) && (a[child].key < a[child + 1].key)) {
			child++;
		}
		if (rootkey > a[child].key) {
			break;
		}
		else {
			a[child / 2] = a[child];
			child *= 2;
		}
	}
	a[child / 2] = temp;
}

void SWAP(element* a, element* b) {
	element temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void heapSort(element a[], int n) {
	int i, j;
	//element temp;
	for (i = n / 2; i > 0; i--) {
		adjust(a, i, n);
	}
	for (i = n - 1; i > 0; i--) {
		SWAP(&a[1], &a[i + 1]);
		adjust(a, 1, i);
	}
}

void reduce(element array[]) {
	int a, b;
	while (total > 1) {
		heapSort(array, total);
		a = array[total].key;
		b = array[total - 1].key;
		total--;
		array[total].key = a - b;
	}
}

int main() {
	init();
	reduce(array);
	printf("%d", array[total].key);
	
	return 0;
}