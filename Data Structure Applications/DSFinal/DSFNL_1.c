#define _CRT_SECURE_NO_WARNINGS
#define MAX_NUM 10000
#include <stdio.h>
#include <stdlib.h>

int primeCheck(int k) {
	int i;
	if (k == 1)
		return 0;
	for (i = 2; i < k; i++) {
		if (k%i == 0) {
			return 0;
		}
	}
	return 1;
}

int main() {
	FILE*fp = fopen("input.txt", "r");
	int n, result;
	fscanf(fp, "%d", &n);
	if (n > MAX_NUM)
		printf("Too BIg\n");
	else {
		result = primeCheck(n);
		if (result)
			printf("Prime\n");
		else
			printf("Not Prime\n");
	}
	fclose(fp);
	return 0;
}