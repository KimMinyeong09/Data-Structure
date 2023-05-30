#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 100
#include <stdio.h>
#include <stdlib.h>

typedef enum {
	lparen, rparen, plus, minus, times, divide, mod, eos, operand
}precedence;

static int isp[] = { 0,19,12,12,13,13,13,0 };
static int icp[] = { 20,19,12,12,13,13,13,0 };

int stack_eval[MAX_SIZE];
precedence stack_postfix[MAX_SIZE];
char expr[MAX_SIZE];

void push(int* top, int item) {
	if (*top >= MAX_SIZE - 1) {
		printf("Stack is full.\n");
	}
	else
		stack_eval[++(*top)] = item;
}

int pop(int* top) {
	if (*top < 0) {
		printf("Stack is empty.\n");
		return -1;
	}
	else
		return stack_eval[(*top)--];
}

void push_postfix(int* top, precedence item) {
	if (*top >= MAX_SIZE - 1)
		printf("Stack is full.\n");
	else {
		++(*top);
		stack_postfix[*top] = item;
	}	
}

precedence pop_postfix(int* top) {
	if (*top < 0) {
		printf("Stack is empty.\n");
		return eos;
	}
	else
		return stack_postfix[(*top)--];
}

char makeToken(precedence token) {
	switch (token) {
	case plus: return '+';
	case minus: return '-';
	case times: return '*';
	case divide: return '/';
	case mod: return '%';
	default: return ' ';
	}
}

precedence getToken(char* symbol, int* n) {
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case NULL:case ' ': return eos;
	default: return operand;
	}
}

int eval(void){	
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0;
	int top = -1;
	token = getToken(&symbol, &n);
	while (token != eos) {
		if (token == operand) {
			push(&top, symbol - '0');
		}
		else {
			op2 = pop(&top);
			op1 = pop(&top);
			switch (token) {
			case plus: 
				push(&top, op1 + op2); break;
			case minus: 
				push(&top, op1 - op2); break;
			case times: 
				push(&top, op1 * op2); break;
			case divide: 
				push(&top, op1 / op2); break;
			case mod: 
				push(&top, op1 % op2); break;
			}
		}
		token = getToken(&symbol, &n);
	}
	return pop(&top);
}

void postfix(void){
	char symbol;
	int i = 0, n = 0;
	int top = -1;
	precedence token;
	token = getToken(&symbol, &n);
	while (token != eos) {
		switch (token) {
		case operand:
			expr[i++] = symbol;
			break;
		case rparen:
			while (stack_postfix[top] != lparen) 
				expr[i++] = makeToken(pop_postfix(&top));
			token = pop_postfix(&top);
			break;
		default:
			while (icp[token] <= isp[stack_postfix[top]])
				expr[i++] = makeToken(pop_postfix(&top));
			push_postfix(&top, token);
			break;
		}
		token = getToken(&symbol, &n);
	}
	while (top > -1) 
		expr[i++] = makeToken(pop_postfix(&top));
	expr[i] = NULL;
}



int main() {	
	int result,i=0,j=0,n;
	char temp;
	FILE* fp = fopen("input.txt", "r");
	
	while (1) {
		fscanf(fp, "%c", &expr[i++]);
		if (feof(fp))
			break;
	}
	printf("input.txt\n");
	printf("%s\n\n", expr);
	postfix();
	printf("Postfix: %s\n", expr);
	result = eval();
	printf("Result : %d\n", result);

	fclose(fp);
	return 0;

}