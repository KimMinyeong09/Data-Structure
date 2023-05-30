#define _CRT_SECURE_NO_WARNINGS
#define MAX_NUM 100
#include <stdio.h>
#include <stdlib.h>

typedef enum { plus, minus, times, divide, mod, exp, eos, operand }precedence;
char expr[MAX_NUM];
int stack[MAX_NUM];

precedence getToken(char *symbol, int*n) {
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '+':
		return plus;
	case '-':
		return minus;
	case '*':
		return times;
	case '/':
		return divide;
	case '%':
		return mod;
	case '^':
		return exp;
	case NULL:case ' ':
		return eos;
	default:
		return operand;
	}
}

void push(int i, int *top) {
	if ((*top) >= (MAX_NUM-1)) {
		fprintf(stderr, "stack Full\n");
		exit(EXIT_FAILURE);
	}
	stack[++(*top)] = i;
}

int pop(int *top) {
	if ((*top) ==-1) {
		fprintf(stderr, "stack Empty\n");
		exit(EXIT_FAILURE);
	}
	return stack[(*top)--];
}

int eval() {
	precedence token;
	char symbol;
	int op1, op2, temp;
	int n = 0, i;
	int top = -1;
	token = getToken(&symbol, &n);
	while (token != eos) {
		if (token == operand)
			push(symbol - '0', &top);
		else {
			op2 = pop(&top);
			op1 = pop(&top);
			switch (token) {
			case plus: 
				push(op1 + op2, &top);
				break;
			case minus:
				push(op1 - op2, &top);
				break;
			case times:
				push(op1 * op2, &top);
				break;
			case divide:
				push(op1 / op2, &top);
				break;
			case mod:
				push(op1 % op2, &top);
				break;
			case exp:
				temp = 1;
				for (i = 0; i < op2; i++)
					temp *= op1;
				push(temp, &top);
				break;
			}
		}
		token = getToken(&symbol, &n);
	}
	return pop(&top);
}

int main() {
	FILE*fp = fopen("input.txt", "r");
	int i = 0;
	while (1) {
		fscanf(fp, "%c", &expr[i++]);
		if (feof(fp)) 
			break;
	}
	
	int result;
	result = eval();
	printf("%d", result);
	fclose(fp);
	return 0;
}