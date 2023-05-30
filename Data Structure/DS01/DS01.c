#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100
#include <stdio.h>
#include <stdlib.h>

char stack[MAX_STACK_SIZE] = { 0 };
int index = -1;

void push(char bracket) {
	index++;
	stack[index] = bracket;
}

char pop() {
	index--;
	return stack[index + 1];
}

int IsEmpty() {
	if (index == -1)
		return 1;
	else
		return 0;
}

int checking(char temp, char check) {
	if (temp == ')') {
		if (check == '(')
			return 1;
		else
			return 0;
	}
	else if (temp == '}') {
		if (check == '{')
			return 1;
		else
			return 0;
	}
	else if (temp == ']') {
		if (check == '[')
			return 1;
		else
			return 0;
	}
	else if (temp == '>') {
		if (check == '<')
			return 1;
		else
			return 0;
	}
}

void prtResult(int x) {
	if (x)
		printf("balanced");
	else
		printf("not balanced");
}

int main() {
	char temp, check;
	int balanced = 1, i = 0;
	FILE* fp = fopen("input.txt", "r");

	printf("*input.txt*\n");
	while (1) {
		fscanf(fp, "%c", &temp);
		if (feof(fp))
			break;
		printf("%c", temp);
	}printf("\n");

	fseek(fp, 0, SEEK_SET);

	while (1) {
		fscanf(fp, "%c", &temp);
		if (feof(fp))
			break;

		if ((temp == '(') | (temp == '{') | (temp == '[') | (temp == '<')) {
			push(temp);
		}

		else if ((temp == ')') | (temp == '}') | (temp == ']') | (temp == '>')) {
			if (IsEmpty() == 0) {
				check = pop();

				if (checking(temp, check) == 0) {
					balanced = 0;
					break;
				}
			}
			else {
				balanced = 0;
				break;
			}
		}
	}

	if (index != -1)
		balanced = 0;
		
	printf("*Output*\n");
	prtResult(balanced);

	return 0;
}