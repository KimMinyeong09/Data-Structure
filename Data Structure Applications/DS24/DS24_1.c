#define _CRT_SECURE_NO_WARNINGS
#define MAX_TABLE 1000
#include <stdio.h>
#include <stdlib.h>

int ht[MAX_TABLE] = { 0 };
int tableNum = 0;
int inputNum = 0;
int searchNum = 0;

int h(int k) {
	int temp;
	temp = k % tableNum;
	return temp;
}

int search(int k) {
	int homeBucket, currentBucket;
	homeBucket = h(k);
	for (currentBucket = homeBucket; (ht[currentBucket]) && (ht[currentBucket] != k);) {
		currentBucket = (currentBucket + 1) % tableNum;
		if (currentBucket == homeBucket)
			return -1;
	}
	if (ht[currentBucket] == k) {
		return ht[currentBucket];
	}
	return -1;
}

void hashing(int k, int temp) {
	if (!(ht[k])) {
		ht[k] = temp;
	}
	else {
		k = h(k + 1);
		hashing(k, temp);
	}
}

void printTable() {
	int i;
	printf("Hash Table:\n");
	for (i = 0; i < tableNum; i++) {
		printf("%d: ", i);
		if (ht[i])
			printf("%d\n", ht[i]);
		else
			printf("\n");
	}
}

void init() {
	int temp, i, k;
	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%d %d %d", &tableNum, &inputNum, &searchNum);
	for (i = 0; i < inputNum; i++) {
		fscanf(fp, "%d", &temp);
		k = h(temp);
		hashing(k, temp);
	}
	printTable();

	printf("Search:\n");
	for (i = 0; i < searchNum; i++) {
		fscanf(fp, "%d", &temp);
		k = search(temp);
		if (k < 0)
			printf("F");
		else
			printf("S");
	}

	fclose(fp);
}

int main() {
	init();
	return 0;
}