#define _CRT_SECURE_NO_WARNINGS
#define MAX_NODE 10001
#include <stdio.h>
#include <stdlib.h>

int treeList[MAX_NODE];
int leaf[MAX_NODE];
int leaf_top = -1;
int index = 0;
int max = 0;
int min = 0;

void init() {
	FILE* fp = fopen("input.txt", "r");
	while (1) {
		if (feof(fp))
			break;
		index++;
		fscanf(fp, "%d", &treeList[index]);
	}
	fclose(fp);
}

int sum(int leaf) {
	int result = 0;
	while (1) {
		result += treeList[leaf];
		if (leaf == 1)
			break;
		leaf /= 2;
	}
	return result;
}

void leafList() {
	int i = 1;
	int stack_top = -1;
	int stack[MAX_NODE];
	while (1) {
		while (index >= i) {
			stack[++stack_top] = i;
			i *= 2;
		}
		if (stack_top == -1)
			return;

		i = stack[stack_top];
		stack_top--;
		if (i * 2 > index) {
			leaf[++leaf_top] = i;
		}
		i = 2 * i + 1;
	}
}

void sumMax() {
	int temp = 0;
	int j;
	leafList();

	j = leaf[leaf_top--];
	max = sum(j);

	while (leaf_top > -1) {
		j = leaf[leaf_top--];
		temp = sum(j);
		if (max < temp) {
			max = temp;
		}
	}
}

void sumMin() {
	int temp = 0;
	int j;
	leafList();

	j = leaf[leaf_top--];
	min = sum(j);

	while (leaf_top > -1) {
		j = leaf[leaf_top--];
		temp = sum(j);
		if (min > temp) {
			min = temp;
		}
	}
}

int main() {
	init();
	sumMax();
	sumMin();

	printf("%d %d", max, min);

	return 0;
}