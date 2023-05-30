#define _CRT_SECURE_NO_WARNINGS
#define MAX_VERTICES 100
#define SWAP(x,y,t) ((t)=(x),(x) = (y),(y)=(t))
#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int from;
	int to;
	int value;
}element;
element list[MAX_VERTICES*(MAX_VERTICES - 1) / 2];
element edge[MAX_VERTICES];
int parent[MAX_VERTICES];

void quickSort(element a[], int left, int right) {
	int pivot, i, j;
	element temp;
	if (left < right) {
		i = left;
		j = right + 1;
		pivot = a[left].value;
		do {
			do i++; while (a[i].value < pivot);
			do j--; while (a[j].value > pivot);
			if (i < j)
				SWAP(a[i], a[j], temp);
		} while (i < j);
		SWAP(a[left], a[j], temp);
		quickSort(a, left, j - 1);
		quickSort(a, j + 1, right);
	}
}

void weight(int first, int second) {
	int sum;
	sum = parent[first] + parent[second];
	if (parent[first] < parent[second]) {
		parent[second] = first;
		parent[first] = sum;
	}
	else {
		parent[first] = second;
		parent[second] = sum;
	}
}

int findRoot(int i) {
	int trail, root,lead;
	for (root = i; (parent[root]) >= 0; root = parent[root]);
	return root;
}

int main() {
	FILE *fp = fopen("input.txt", "r");
	int i, j;
	int sum = 0;
	int N, temp, count = -1;
	int left = 0;
	int num = 0;
	fscanf(fp, "%d", &N);
	for (i = 0; i < N; i++)
		parent[i] = -1;
	for (i = 0; i < N; i++){
		for (j = 0; j <= i; j++) {
			fscanf(fp, "%d", &temp);
		}
		for (j = i + 1; j < N; j++) {
			fscanf(fp, "%d", &temp);
			if (temp) {
				list[++count].from = i;
				list[count].to = j;
				list[count].value = temp;
			}
		}
	}
	quickSort(list, left, count);
	i = 0, j = 0;
	int fromn, ton;
	while (num != N - 1) {
		if ((fromn = findRoot(list[i].from)) != (ton=findRoot(list[i].to))) {
			weight(fromn, ton);
			edge[j++] = list[i];
			sum += list[i].value;
		}
		i++;
	}
	printf("%d",sum);

	return 0;
}