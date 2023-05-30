#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

int main() {
	FILE* fp1 = fopen("unsorted.txt", "w+");
	FILE* fp2 = fopen("sorted.txt", "w+");

	int N, random, i, j, temp;
	float gap;
	time_t start, end;
	srand(time(NULL));
	printf("N: ");
	scanf("%d", &N);
	int* arr = (int*)malloc(sizeof(int) * N);

	for (i = 0; i < N; i++) {
		arr[i] = rand();
		fprintf(fp1, "%d ", arr[i]);
	}
	
	start = clock();
	for (int i = 0; i < N - 1; i++){
		for (int j = i; j < N; j++) {
			if (arr[i] < arr[j]) {
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
	end = clock();
	gap = (float)(end - start);

	for (i = 0; i < N; i++) {
		fprintf(fp2, "%d ", arr[i]);
	}

	printf("Time: %f", gap);

	fclose(fp1);
	fclose(fp2);
	free(arr);
	return 0;
}