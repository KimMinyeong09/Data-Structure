#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int Prime(int num) {
	int i;
	if (num == 1)
		return 0;
	else if (num >= 2) {
		for (i = 2; i < num; i++) {
			if (num % i == 0) {
				return 0;
				break;
			}
		}
		return 1;
	}
}


int main() {
	int x;
	printf("Number: ");
	scanf("%d", &x);

	if (Prime(x))
		printf("Prime");
	else
		printf("Not Prime");

	return 0;
}