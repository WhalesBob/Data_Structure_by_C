/*
1. [�����Ҵ� �迭�� ����] ������ ���� ������ �����ϰ� ���� ���� ���� ����Ǵ� ���α׷��� �ۼ��϶�.
push �� �� ������ full�̸� ���� ���� ������ ����ϰ� ����, pop �� �� ������ empty�̸� ���� �޽����� ����ϰ� ������. 
���ؿ� ���� ����� input.txt ���Ͽ� ������, ���ؾȿ� ������ ������ �л��� ���� �����̰�, ������ ũ��� 5�̴�.

���� ó�� ���
push id name // stack�� ������ ����, full�̸� ���� ���� ������ ����ϰ� ����
pop // stack�� ������ ����, empty�̸� ���� �޽����� ����ϰ� ����
sprint // stack�� ������ ����Ʈ
quit // ���α׷� ���� ����. �߸��� ��ɾ� // �޽��� ������ ���

[���� ����]
#define MAX_STACK_SIZE 5
typedef struct {
int id; // unique id
char name[MAX_NAME_SIZE]; // last name
} element;
element stack[MAX_STACK_SIZE];

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 5
#define MAX_NAME_SIZE 100
#define MAX_LEN 100

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
}element;

element stack[MAX_STACK_SIZE];
int top = -1;

void stackFull(void);
void stackEmpty(void);
void push(element item);
element pop(void);
void sprint(void);
void quit(void);

int main(void) {

	char* delimiter = " \n";
	char* context;
	char* op = NULL;
	element student;
	FILE* fp;
	fopen_s(&fp, "input.txt", "r");
	char line[MAX_LEN];

	printf("<<stack operations where MAX_STACK_SIZE is 5>>\n");
	printf("The format of the stack operation is as follows!!\n");
	printf("push 1 Jung\n");
	printf("pop\n\n");
	printf("***************************************************\n");

	if (fp == NULL) {
		fprintf(stderr, "Cannot open this file");
		exit(EXIT_FAILURE);
	}

	while(1){
		if (!fgets(line, MAX_LEN, fp)) {
			break;
		}
		op = strtok_s(line, delimiter, &context);

		if (!strcmp(op, "push")) {
			sscanf_s(context, "%d %s", &student.id, &student.name, sizeof(student.name));
			push(student);
		}
		else if (!strcmp(op, "pop")) {
			student = pop();
		}
		else if (!strcmp(op, "sprint")) {
			sprint();
			printf("\n");
		}
		else if (!strcmp(op, "quit")) {
			quit();
		}
		else {
			printf("wrong command! try again!\n");
		}
	}

	return 0;
}
void stackFull(void) {
	fprintf(stderr, "stack is full, cannot add element\n");
	printf("current stack elements : \n");
	while (top != -1) {
		element str = pop();
		printf("%d %s\n", str.id, str.name);
	}
	exit(EXIT_FAILURE);
}
void stackEmpty(void) {
	fprintf(stderr, "stack is empty, cannot show element to you\n");
	exit(EXIT_FAILURE);
}
void push(element item) {
	if (top >= MAX_STACK_SIZE - 1) {
		stackFull();
	}
	stack[++top] = item;
}
element pop(void) {
	if (top == -1) {
		stackEmpty();
	}
	return stack[top--];
}
void sprint(void) {
	int reader = top;
	for (int i = reader; i >= 0; i--) {
		printf("%d %s \n", stack[i].id, stack[i].name);
	}
}
void quit(void) {
	printf("Quit stack program\n");
	exit(EXIT_SUCCESS);
}
