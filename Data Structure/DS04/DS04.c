#define _CRT_SECURE_NO_WARNINGS
#define MAX_VERTICES 100
#define TRUE 1
#define FALSE 0
#include <stdio.h>
#include <stdlib.h>

typedef struct node* nodePointer;
struct node {
	int vertex;
	nodePointer link;
}node;

nodePointer graph[MAX_VERTICES];
int total_vertex = 0;
int mother[MAX_VERTICES];
short int dfs_visited[MAX_VERTICES];

void insertEdge(nodePointer* head, int vertex1, int vertex2) {
	nodePointer trail, temp, element;
	trail = *head;
	temp = (nodePointer)malloc(sizeof(node));
	temp->vertex = vertex2;
	temp->link = NULL;

	if (!(*head)) {
		*head = temp;
	}
	else {
		while ((trail->link) != NULL) {
			trail = trail->link;
		}
		trail->link = temp;
	}
}

void init() {
	FILE* fp = fopen("input.txt", "r");
	int temp;
	int i, j;
	fscanf(fp, "%d", &total_vertex);

	for (int x = 0; x < total_vertex; x++) {
		graph[x] = (nodePointer)malloc(sizeof(node));
		graph[x] = NULL;
		dfs_visited[x] = FALSE;
	}
	for (i = 0; i < total_vertex; i++) {
		for (j = 0; j < total_vertex; j++) {
			fscanf(fp, "%d", &temp);
			if (temp) {
				insertEdge(&graph[i], i, j);
			}
		}
	}
	fclose(fp);
}

void initVisited() {
	for (int x = 0; x < total_vertex; x++) 
		dfs_visited[x] = FALSE;
}

void dfs(int v) {
	nodePointer w;
	dfs_visited[v] = TRUE;
	for (w = graph[v]; w; w = w->link)
		if (!(dfs_visited[w->vertex])) {
			dfs(w->vertex);
		}
}

int checking() {
	int i;
	for (i = 0; i < total_vertex; i++) {
		if (dfs_visited[i] == FALSE)
			break;
	}
	if (i == total_vertex)
		return TRUE;
	else
		return FALSE;
}

int FindMother() {
	int i, count = 0;
	for (i = 0; i < total_vertex; i++) {
		initVisited();
		dfs(i);
		if (checking() == TRUE) {
			mother[count] = i;
			count++;
		}
	}
	return count;
}

int main() {
	int result, i;
	init();
	result = FindMother();
	if (result > 0) {
		printf("Mother vertex: ");
		for (i = 0; i < result; i++) {
			printf("%d ", mother[i]);
		}
	}
	else {
		printf("No mother vertex.");
	}

	return 0;
}