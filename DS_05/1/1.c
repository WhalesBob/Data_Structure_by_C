/*
1. [정적할당 배열의 스택] 다음과 같은 스택을 생성하고 실행 예와 같이 수행되는 프로그램을 작성하라.
push 할 때 스택이 full이면 스택 안의 내용을 출력하고 종료, pop 할 때 스택이 empty이면 오류 메시지를 출력하고 종료함. 
스텍에 대한 명령은 input.txt 파일에 있으며, 스텍안에 저장할 내용은 학생에 대한 정보이고, 스택의 크기는 5이다.

스택 처리 명령
push id name // stack에 데이터 삽입, full이면 스택 안의 내용을 출력하고 종료
pop // stack에 데이터 삭제, empty이면 오류 메시지를 출력하고 종료
sprint // stack의 내용을 프린트
quit // 프로그램 수행 종료. 잘못된 명령어 // 메시지 오류를 출력

[스택 정의]
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
