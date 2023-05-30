#define _CRT_SECURE_NO_WARNINGS
#define MAX_VERTEX 100
#include <stdio.h>
#include <stdlib.h>

int vertexTotal = 0;
int edgeMax = 0;
int edgeLimit = 0;
int totalCost = 0;

typedef struct {
	int from;
	int to;
	int cost;
}edgeCost;
edgeCost edgelist[MAX_VERTEX];
edgeCost edgeResult[MAX_VERTEX];
int parent[MAX_VERTEX];

void init() {
	FILE* fp = fopen("input.txt", "r");
	int i, j, temp;
	fscanf(fp, "%d", &vertexTotal);
	edgeLimit = vertexTotal - 1;

	for (i = 0; i < vertexTotal; i++) {
		for (j = 0; j < i+1; j++) {
			fscanf(fp, "%d", &temp);
		}
		for (j = i + 1; j < vertexTotal; j++) {
			fscanf(fp, "%d", &temp);
			if (temp != 0) {
				edgelist[edgeMax].from = i;
				edgelist[edgeMax].to = j;
				edgelist[edgeMax].cost = temp;
				edgeMax++;
			}
		}
	}

	for (i = 0; i < vertexTotal; i++)
		parent[i] = -1;
	fclose(fp);
}

void sortMin() {
	int i, j;
	edgeCost temp;
	for (i = 0; i < edgeMax; i++) {
		for (j = i + 1; j < edgeMax; j++) {
			if (edgelist[i].cost > edgelist[j].cost) {
				temp = edgelist[i];
				edgelist[i] = edgelist[j];
				edgelist[j] = temp;
			}
		}
	}
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

void kruskal(){
	int fromroot, toroot;
	int e = 0;
	int i = 0;
	edgeCost temp;
	while (e < edgeLimit){
		temp = edgelist[i];
		i++;
		if ((fromroot = collapsingFind(temp.from)) != (toroot = collapsingFind(temp.to))) {
			totalCost += temp.cost;
			edgeResult[e] = temp; e++;
			weightedUnion(fromroot, toroot);
		}
	}
}
	
void print() {
	int i;
	printf("Selected Edges: ");
	printf("(%d, %d)", edgeResult[0].from, edgeResult[0].to);
	for (i = 1; i < edgeLimit; i++) {
		printf(", (%d, %d)", edgeResult[i].from, edgeResult[i].to);
	}
	printf("\n");
	printf("Cost: %d\n",totalCost);
}

int main() {
	init();
	sortMin();
	kruskal();
	print();

	return 0;
}