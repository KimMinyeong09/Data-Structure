#define _CRT_SECURE_NO_WARNINGS
#define MAX_VERTICES 100
#include <stdio.h>
#include <stdlib.h>

typedef struct node* nodePointer;
typedef struct node {
	int vertex;
	nodePointer link;
};

typedef struct {
	int count;
	nodePointer link;
}hdnodes;
hdnodes graph[MAX_VERTICES];
int vertexTotal = 0;

void insertEdge(int vertex1, int vertex2) {
	nodePointer temp1, temp2;
	temp1 = (nodePointer)malloc(sizeof(nodePointer));
	temp1->vertex = vertex2;
	temp1->link = NULL;
	if (graph[vertex1].link == NULL){
		graph[vertex1].link = temp1;
	}
	else{
		temp2 = graph[vertex1].link;
		while (temp2->link)		{
			temp2 = temp2->link;
		}
		temp2->link = temp1;
	}
	graph[vertex2].count++;
}

void init() {
	int i, j, x;
	nodePointer temp;
	temp = (nodePointer)malloc(sizeof(nodePointer));
	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &vertexTotal);

	for (i = 0; i < vertexTotal; i++) {
		graph[i].count = 0;
		graph[i].link = NULL;
	}

	for (i = 0; i < vertexTotal; i++) {
		for (j = 0; j < vertexTotal; j++) {
			fscanf(fp, "%d", &x);
			if (x) {
				insertEdge(i, j);
			}
		}
	}
	fclose(fp);
}

void stackInput(int i, nodePointer* a){
	nodePointer temp1, temp2;
	temp1 = (nodePointer)malloc(sizeof(nodePointer));
	temp1->vertex = i;
	temp1->link = NULL;
	temp2 = *a;

	if (!(*a)) {
		*a = temp1;
	}
	else {
		while ((temp2->link) != NULL) {
			temp2 = temp2->link;
		}
		temp2->link = temp1;
	}
}

void topSort() {
	int i, j, k;
	int count = 0;
	nodePointer temp, stack;
	stack = (nodePointer)malloc(sizeof(nodePointer));
	stack = NULL;
	while (1) {
		if (count == vertexTotal)
			break;
		for (i = vertexTotal - 1; i >= 0; i--) {
			if (graph[i].count == 0) {
				stackInput(i, &stack);
			}
		}
		for (; stack; stack = stack->link) {
			k = stack->vertex;
			printf("%d ", k);
			count++;
			graph[k].count--;
			for (temp = graph[k].link; temp; temp = temp->link)	{
				j = temp->vertex;
				graph[j].count--;
				if ((graph[j].count == 0) && (graph[j].link == NULL)) {
					printf("%d ", j);
					graph[j].count--;
					count++;
				}
			}
		}
	}
}

int main() {
	init();	
	topSort();

	return 0;
}