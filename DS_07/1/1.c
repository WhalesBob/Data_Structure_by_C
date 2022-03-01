/*
1. 후위표기법(postfix notation)으로 표현된 하나의 수식을 파일(input.txt)로 입력받아 그 계산 
결과를 화면과 파일에 동시에 출력하는 프로그램을 작성하라. 사용되는 연산자 : +, -, *, /, % 이며,
피연산자는 1~9 사이의 한 자리 정수이다
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100

int top = -1;

typedef enum{  plus, minus, times, divide, mod, eos, operand }precendence;

int stack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE];

precendence getToken(char* symbol, int* n);
void stackFull(void);
void stackEmpty(void);
void push(int item);
int pop(void);

int main(void) {

	FILE* inputFile, * outputFile;
	fopen_s(&inputFile, "input.txt", "r");
	fopen_s(&outputFile, "output.txt", "w");
	
	if (inputFile == NULL) {
		fprintf(stderr, "Cannot open input or output file \n");
		exit(EXIT_FAILURE);
	}
	if (outputFile == NULL) {
		fprintf(stderr, "Cannot open input or output file \n");
		exit(EXIT_FAILURE);
	}

	if (!fgets(expr,MAX_EXPR_SIZE,inputFile)) {
		printf("No context in inputFile \n");
		exit(EXIT_FAILURE);
	}

	fprintf(stdout,"Postfix expression : %s \n", expr);
	fprintf(outputFile, "Postfix expression : %s \n", expr);
	
	precendence token;
	char symbol;
	int op1, op2;
	int n = 0;

	token = getToken(&symbol, &n);

	while (token != eos) {
		if (token == operand) {
			push(symbol - '0');
		}
		else {
			op2 = pop();
			op1 = pop();
			switch (token) {
			case plus:
				push(op1 + op2);
				break;
			case minus:
				push(op1 - op2);
				break;
			case times:
				push(op1 * op2);
				break;
			case divide:
				push(op1 / op2);
				break;
			case mod:
				push(op1 % op2);
			}
		}
		token = getToken(&symbol, &n);
	}
	int result = pop();
	fprintf(stdout,"The evaluation value : %d \n", result);
	fprintf(outputFile, "The evaluation value : %d \n", result);

	return 0;
}

precendence getToken(char* symbol, int* n) {
	*symbol = expr[(*n)++];
	
	switch (*symbol) {
		case '+':
			return plus;
		case '-':
			return minus;
		case '/':
			return divide;
		case '*':
			return times;
		case '%':
			return mod;
		case '\0':
			return eos;
		default :
			return operand;
	}
}

void stackFull(void) {
	fprintf(stderr, "stack is full, cannot add element\n");
	exit(EXIT_FAILURE);
}
void stackEmpty(void) {
	fprintf(stderr, "stack is empty, cannot show element to you\n");
	exit(EXIT_FAILURE);
}
void push(int item) {
	if (top >= MAX_STACK_SIZE - 1) {
		stackFull();
	}
	stack[++top] = item;
}
int pop(void) {
	if (top == -1) {
		stackEmpty();
	}
	return stack[top--];
}