#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	char code[11];
	int i, sum = 0;
	int missing, result, temp;

	printf("ISBN: ");
	scanf("%s", code);

	for (i = 0; i < 10; i++) {
		if (code[i]== '?') {
			missing = 10 - i;
		}
		else if (code[i]== 'X') {
			sum += 10 * (10 - i);
		}
		else {
			temp = (int)(code[i]) - 48;
			sum += (temp) * (10 - i);
		}
	}
	
	for (i = 0; i < 10; i++) {
		if (((sum + i * missing) % 11) == 0) {
			result = i;
			break;
		}
	}

	printf("Missing Digit: %d", result);
	return 0;
}