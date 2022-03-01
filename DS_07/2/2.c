/*
2. 중위표기법(infix notation)으로 표현된 하나의 수식을 파일로 입력받아 후위표기법(postfix
notation)으로 변환하여 화면 및 파일에 동시에 출력하는 프로그램을 작성하라.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_EXPR_SIZE 100
#define MAX_STACK_SIZE 100

int top = -1;

typedef enum {lparen, rparen, plus, minus, times, divide, mod, eos, operand }precendence;

char expr[MAX_EXPR_SIZE];
precendence stack[MAX_STACK_SIZE];

static int isp[] = { 0,19,12,12,13,13,13,0 };
static int icp[] = { 20,19,12,12,13,13,13,0 };

void stackFull(void);
void stackEmpty(void);
void push(int item);
int pop(void);
void printToken(precendence item);

int main(void) {

	FILE* inputFile, * outputFile;
	fopen_s(&inputFile, "input.txt", "r");
	fopen_s(&outputFile, "output.txt", "w");

	if ((inputFile == NULL) || (outputFile == NULL)) {
		fprintf(stderr, "Cannot open input or output file \n");
		exit(EXIT_FAILURE);
	}

	if (!fgets(expr, MAX_EXPR_SIZE, inputFile)) {
		printf("No context in inputFile \n");
		exit(EXIT_FAILURE);
	} // 이까지 하면 열림. 그리고 잘 찍혀 나옴.

	printf("<<<<<<<<<< Infix to Postfix >>>>>>>>>> \n");
	printf("Infix expression : %s \n", expr );
	printf("Postfix expression : ");

	char symbol;
	precendence token;
	int n = 0; 
	stack[0] = eos; top = 0;

	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		if (token == operand) {
			printf("%c", symbol);
		}
		else if (token == rparen) {
			while (stack[top] != lparen) {
				printToken(pop());
			}
			pop();
		}
		else {
			while (isp[stack[top]] >= icp[token]) {
				printToken(pop());
			}
			push(token);
		}
	}
	while ((token = pop()) != eos) {
		printToken(token);
	}
	printf("\n");
	return 0;
}
precendence getToken(char* symbol, int* n) {
	*symbol = expr[(*n)++];

	switch (*symbol) {
	case '(':
		return lparen;
	case ')':
		return rparen;
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
	default:
		return operand;
	}
}
void printToken(precendence item) {

	switch (item) {
		case lparen:
			printf("(");
			break;
		case rparen:
			printf(")");
			break;
		case plus:
			printf("+");
			break;
		case minus:
			printf("-");
			break;
		case divide:
			printf("/");
			break;
		case times:
			printf("*");
			break;
		case mod:
			printf("%%");
			break;
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