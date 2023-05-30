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
nodePointer front, rear;
int total_vertex = 0;
short int dfs_visited[MAX_VERTICES];
short int bfs_visited[MAX_VERTICES];

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
		bfs_visited[x] = FALSE;
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

void printAdjacent(nodePointer* vertexNum) {
	int i;
	nodePointer temp;
	for (i = 0; i < total_vertex; i++) {
		temp = vertexNum[i];
		printf("Vertex %d: ", i);
		for (; temp; temp = temp->link) {
			printf("%d ", temp->vertex);
		}
		printf("\n");
	}
}

void dfs(int v) {
	nodePointer w;
	dfs_visited[v] = TRUE;
	printf("%d ", v);
	for (w = graph[v]; w; w = w->link)
		if (!(dfs_visited[w->vertex])) {
			dfs(w->vertex);
		}
}

void addq(int item) {
	nodePointer temp;
	temp = (nodePointer)malloc(sizeof(node));
	temp->vertex = item;
	temp->link = NULL;
	if (front)
		rear->link = temp;
	else
		front = temp;
	rear = temp;
}

int deleteq() {
	nodePointer temp = front;
	int item;
	item = temp->vertex;
	front = temp->link;
	free(temp);
	return item;
}

void bfs(int v) {
	nodePointer w;
	front = rear = NULL;
	printf("%d ", v);
	bfs_visited[v] = TRUE;
	addq(v);
	while (front) {
		v = deleteq();
		for (w = graph[v]; w; w = w->link) {
			if (!(bfs_visited[w->vertex])) {
				printf("%d ", w->vertex);
				addq(w->vertex);
				bfs_visited[w->vertex] = TRUE;
			}
		}
	}
}

int main() {
	init();
	printAdjacent(graph);
	printf("DFS: ");
	dfs(0);
	printf("\n");
	printf("BFS: ");
	bfs(0);
	printf("\n");

	return 0;
}