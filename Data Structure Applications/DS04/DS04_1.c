#define _CRT_SECURE_NO_WARNINGS
#define MAX_DIGIT 100 //자리수 설정

#include <stdio.h>
#include <stdlib.h>

int ASCII(char x) {
	int result;
	result = (int)x - 48;
	return result;
}

void Add(int list1[],int list2[], int len) {
	int add[MAX_DIGIT];
	int temp, x = len, n;
	for (n = 0; n <= x; n++)
		add[n] = 0;

	while (1) { 
		temp = add[x] + list1[x] + list2[x];
		if (x == 0) {
			add[x] = temp;
			break;
		}
		else {
			if (temp >= 10) {
				add[x - 1] += 1;
				add[x] = temp % 10;
			}
			else {
				add[x] = temp;
			}
		}
		x--;
	}
	for (x = 0; x <= len; x++)
		printf("%d", add[x]);

}

void Sub(int list1[], int list2[], int len) {
	int sub[MAX_DIGIT];
	int temp, x = len, n;
	for (n = 0; n <= x; n++)
		sub[n] = 0;

	while (1) {  
		temp = sub[x] + list1[x] - list2[x];
		if (x == 0) {
			sub[x] = temp;
			break;
		}
		else {
			if (temp < 0) {
				sub[x - 1] += (-1);
				sub[x] = (temp + 10);
			}
			else {
				sub[x] = temp;
			}
		}
		x--;
	}
	for (x = 0; x <= len; x++) {
		if (sub[x] > 0) {
			n = x;
			break;
		}
		else
			n = len;
	}
	for (x = n; x <= len; x++)
		printf("%d", sub[x]);
}

int main() {
	FILE* a = fopen("a.txt", "r");
	FILE* b = fopen("b.txt", "r");

	char input1[MAX_DIGIT], input2[MAX_DIGIT];
	int num1[MAX_DIGIT], num2[MAX_DIGIT];
	int add[MAX_DIGIT], sub[MAX_DIGIT];
	int i = 0, j = 0, k = 0, temp;

	fscanf(a, "%s", input1);
	fscanf(b, "%s", input2);

	printf("a.txt\n");
	printf("%s\n", input1);
	printf("b.txt\n");
	printf("%s\n", input2);

	while (1) {
		if (input1[i] == '\0')
			break;
		num1[i] = ASCII(input1[i]);
		i++;
	}
	i--;
	while ((i - j) >= 0) {
		if (48 <= input2[j] && input2[j] <= 57)
			num2[i - j] = ASCII(input2[j]);
		else
			num2[i - j] = 0;
		j++;
	}j--;

	printf("Addition:\n");
	Add(num1, num2, i);
	printf("\nSubtraction:\n");
	Sub(num1, num2, i);

	fclose(a);
	fclose(b);
	
	return 0;
}