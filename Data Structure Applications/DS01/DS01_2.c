#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define MAX 100

int Max(int arr1[],int num1) {
	int max = arr1[0], j;
	for (j = 1; j < num1; j++) {
		if (max < arr1[j])
			max = arr1[j];
	}
	return max;
}

int Min(int arr2[], int num2) {
	int min = arr2[0], k;
	for (k = 1; k < num2; k++) {
		if (min > arr2[k])
			min = arr2[k];
	}
	return min;
}

int main() {
	int text_list[MAX] = { 0 };
	int x=0, i, result1, result2;
	FILE* fp = fopen("input.txt", "rt");
	printf("input.txt ³»¿ë\n");

	while (1) {
		if (feof(fp) != 0) 
			break;
		fscanf(fp, "%d", &i);
		printf("%d ", i);
		text_list[x++] = i;
	}
	printf("\n");
	
	result1 = Min(text_list, x);
	result2 = Max(text_list, x);

	printf("Min: %d\n", result1);
	printf("Max: %d\n", result2);
	
	fclose(fp);

	return 0;
}