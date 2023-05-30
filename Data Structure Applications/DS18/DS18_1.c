#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 100

int n_num = 0, pair_num = 0;
typedef struct {
	int x, y;
}pair;
pair list[MAX_ELEMENT];
int parent[MAX_ELEMENT];
int classNum = 0;

void init() {
	FILE* fp = fopen("input.txt", "r");
	int i;
	fscanf(fp, "%d %d", &n_num, &pair_num);

	for (i = 0; i < n_num; i++) {
		parent[i] = -1;
	}

	for (i = 0; i < pair_num; i++) {
		fscanf(fp, "%d %d", &list[i].x, &list[i].y);
	}

	fclose(fp);
}

void weightedUnion(int i, int j) {
	int temp = parent[i] + parent[j];
	if (parent[i] > parent[j]) {
		parent[i] = j;
		parent[j] = temp;
	}
	else {
		parent[j] = i;
		parent[i] = temp;
	}
}

int collapsingFind(int i) {
	int root, trail, lead;
	for (root = i; parent[root] >= 0; root = parent[root]);
	for (trail = i; trail != root; trail = lead) {
		lead = parent[trail];
		parent[trail] = root;
	}
	return root;
}

void equivalence() {
	int i;
	for (i = 0; i < pair_num; i++) {
		weightedUnion(collapsingFind(list[i].x), collapsingFind(list[i].y));
	}
}

void countClass() {
	int i;
	for (i = 0; i < n_num; i++) {
		if (parent[i] < 0)
			classNum++;
	}
}

void print_equ() {
	int root = 0, i = 0;
	for (; root < n_num; ++root){
		if (parent[root] < 0) {
			printf("New Class: ");
			for (i = 0; i < n_num; ++i)
				if (root == collapsingFind(i))
					printf("%d ", i);
			printf("\n");
		}
	}
}

int main() {
	init();
	equivalence();
	countClass();
	printf("%d\n", classNum);
	print_equ();

	return 0;
}