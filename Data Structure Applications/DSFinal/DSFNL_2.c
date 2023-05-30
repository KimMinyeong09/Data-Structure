#define _CRT_SECURE_NO_WARNINGS
#define MAX_NUM 101
#include <stdio.h>
#include <stdlib.h>

int h(char *f, int d) {
	int n = strlen(f);
	int sum = 0;
	for (int i = 0; i < n-1; i++) {
		if (f[i] >= 97) {
			sum += (f[i] - 96);
		}
		else
			sum += (f[i] - 38);
	}
	return sum;
}



int main() {
	FILE*fp = fopen("input.txt","r");
	int b, num=0, result;
	char key[MAX_NUM];

	fscanf(fp, "%d", &b);
	fscanf(fp, "%c", &key[num]);
	while (1) {
		fscanf(fp, "%c", &key[num++]);
		if (feof(fp))
			break;

	}num--;

	result = h(&key, b);
	printf("%d", result);
	printf(" %d", 'A');
	printf(" %d", 'a');
	


	fclose(fp);
	return 0;
}