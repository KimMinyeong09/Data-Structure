#define _CRT_SECURE_NO_WARNINGS
#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 100
#define MAX_COST 10000000
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int distance[MAX_VERTICES];
short int found[MAX_VERTICES];
int cost[MAX_VERTICES][MAX_VERTICES];
int vertexTotal = 0;
int start = 0;

void init() {
	int i, j, temp;
	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%d %d", &vertexTotal, &start);

	for (i = 0; i < vertexTotal; i++) {
		for (j = 0; j < vertexTotal; j++) {
			fscanf(fp, "%d", &temp);
			if (temp == 0) {
				cost[i][j] = MAX_COST;
			}
			else {
				cost[i][j] = temp;
			}
		}
	}

	fclose(fp);
}

int choose(int distance[], int n, short int found[]) {
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

void shortestPath(int v, int cost[][MAX_VERTICES], int distance[], int n, short int found[]) {
	int i, u, w;
	for (i = 0; i < n; i++) {
		found[i] = FALSE;
		distance[i] = cost[v][i];
	}
	
	found[v] = TRUE;
	distance[v] = 0;
	for (i = 0; i < (n - 2); i++) {
		u = choose(distance, n, found);
		found[u] = TRUE;
		for (w = 0; w < n; w++) {
			if (!found[w]) {
				if (distance[u] + cost[u][w] < distance[w])
					distance[w] = distance[u] + cost[u][w];
			}
		}
	}
}

void print(int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%d ", distance[i]);
	}
	printf("\n");
}

int main() {
	init();
	shortestPath(start, cost, distance, vertexTotal, found);
	print(vertexTotal);

	return 0;
}