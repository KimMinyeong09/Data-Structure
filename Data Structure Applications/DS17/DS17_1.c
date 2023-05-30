#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_RUN 32
#define MAX_KEY 10

int runList[MAX_RUN][MAX_KEY] = { 0 };
int run = 0;

typedef struct {
	int key;
	int index,runNum;
}element;
element Tree[2*MAX_RUN];

void init() {
	int temp, i = 0, j = 0;
	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &run);

	while (1) {
		if (feof(fp))
			break;
		fscanf(fp, "%d", &temp);
		if (temp > 0) {
			runList[i][j] = temp;
			j++;
		}
		else {
			i++;
			j = 0;
		}
	}
	fclose(fp);
}

void winnerTree() {
	int i, j, temp;
	for (i = 0; i < run; i++) {
		Tree[i + run].key = runList[i][0];
		Tree[i + run].index = 0;
		Tree[i + run].runNum = i;
	}
	i = run;
	temp = run / 2;
	while (i > 1) {
		for (j = 0; j < temp; j++) {
			if (Tree[i].key < Tree[i + 1].key) {
				Tree[i/2] = Tree[i];
			}
			else {
				Tree[i/2] = Tree[i + 1];
			}
			i += 2;
		}
		i = temp;
		temp /= 2;
	}
}

void iterInorder() {
	int i = 1;
	int top = -1;
	int stack[MAX_RUN];
	while (1) {
		while (run * 2 > i) {
			stack[++top] = i;
			i *= 2;
		}
		if (top == -1)
			return;

		i = stack[top];
		top--;
		printf("%d ", Tree[i].key);
		i = i * 2 + 1;
	}
}

void print(int n) {
	int i;
	for (i = 1; i < n*2; i++) {
		printf("%d ", Tree[i].key);
	}
}

void Restructuring() {
	int i, j, temp;
	int re_index = Tree[1].index + 1;
	int re_runNum = Tree[1].runNum;
	
	Tree[run+re_runNum].key = runList[re_runNum][re_index];

	i = run;
	temp = run / 2;

	while (i > 1) {
		for (j = 0; j < temp; j++) {
			if (Tree[i].key < Tree[i + 1].key) {
				Tree[i / 2] = Tree[i];
			}
			else {
				Tree[i / 2] = Tree[i + 1];
			}
			i += 2;
		}
		i = temp;
		temp /= 2;
	}
}

int main() {
	init();
	
	winnerTree();
	printf("Winner : %d\n", Tree[1].key);

	printf("Level Order : ");
	print(run);
	printf("\n");

	printf("Inorder : ");
	iterInorder();
	printf("\n");

	Restructuring();
	printf("Winner : %d\n", Tree[1].key);

	printf("Level Order : ");
	print(run);
	printf("\n");

	printf("Inorder : ");
	iterInorder();
	printf("\n");

	return 0;
}