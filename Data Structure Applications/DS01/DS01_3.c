#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int Total_div(int x) {
	int i, result=0;
	for (i = 1; i < x; i++) {
		if (x % i == 0) {
			result += i;
		}
	}
	return result;
}

int main() {
	int num1, num2;
	int sum1, sum2;
	printf("First number: ");
	scanf("%d", &num1);
	printf("Second number: ");
	scanf("%d", &num2);
	
	sum1 = Total_div(num1);
	sum2 = Total_div(num2);

	if (num1 == sum2 && num2 == sum1)
		printf("Amicable");
	else
		printf("Not Amicable");

	return 0;
}