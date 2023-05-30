#define _CRT_SECURE_NO_WARNINGS
#define INFINITE 100000
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#include <stdio.h>
#include <stdlib.h>

int list[MAX_VERTICES];
int t = -1;

int choose(int distance[], int n, short int found[]) {
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++) {
		if ((distance[i] < min) && !found[i]) {
			min = distance[i];
			minpos = i;
		}
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
	list[++t] = v;
	for (i = 0; i < n - 2; i++) {
		u = choose(distance, n, found);
		found[u] = TRUE;
		for (w = 0; w < n; w++) {
			if (!found[w])
				if (distance[w] > distance[u] + cost[u][w]) {
					distance[w] = distance[u] + cost[u][w];
				}
		}
	}
}

int main() {
	int cost[MAX_VERTICES][MAX_VERTICES];
	int distance[MAX_VERTICES];
	short int found[MAX_VERTICES];
	int i, j, N, S, D;
	int temp;
	FILE *fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &N);
	fscanf(fp, "%d", &S);
	fscanf(fp, "%d", &D);
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			fscanf(fp, "%d", &temp);
			if (temp) {
				cost[i][j] = temp;
			}
			else {
				cost[i][j] = INFINITE;
			}
		}
	}
	shortestPath(S, cost, distance, N, found);

	printf("Distance: %d\n", distance[D]);
	printf("Path: ");
	for (i = 0; i <= t; i++) {
		printf("%d ", list[i]);
	}
	/*path ±¸Çö*/
	fclose(fp);
	return 0;
}