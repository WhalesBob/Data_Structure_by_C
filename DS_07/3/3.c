/*
3. 한 개의 arry를 사용하여 multistack을 만들어서 처리하는 프로그램을 작성하시오. 배열의 크기는 10이며 배열안의 원소는 스트링으로 처리한다. 
스택의 개수는 입력을 받아 정한다. 각 스택의 크기는 10/(스택수)로 균일하게 한다.
단 마지막 스텍의 원소는 다른 스텍의 원소 수보다 많을 수 있다. 스택의 번호는 0번부터 시작하며, 스택의 수가 3개이면 스택번호는 0, 1, 2 가 된다. 
스택 처리 명령어는 input.txt 파일에서 입력 받도록 한다.

[스택 처리 명령어]
add 스택번호 스트링 : 해당 스택에 스트링 삽입, full이면 스텍 full 메시지 출력
delete 스택번호 : 해당 스택에 스트링 삭제, empty이면 스텍 empty 메시지 출력
sprint 스택번호 : 해당스택안의 top부터 bottom 내용을 출력
quit : 프로그램 수행 종료. 프로그램 종료 메시지 출력하고 모든 스택의 내용을
출력한다. 명령어 오류시 “wrong command, try again!!” 메시지 출력
스택번호 오류시 “stack number error, try again” 메시지 출력
실행의 예를 참조하여 프로그램을 작성할 것.

[스택 정의]
typedef struct {
int id; // unique id
char name[MAX_NAME_SIZE]; // last name
} element;
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_SIZE 10
#define MAX_STACKS 10
#define MAX_NAME_SIZE 100
#define MAX_LEN 100

int n;

typedef struct {
	char name[MAX_NAME_SIZE];
}element;

element memory[MEMORY_SIZE];
int top[MAX_STACKS];
int boundary[MAX_STACKS];

void stackFull(int i);
void stackEmpty(void);
void push(int i,element item);
element pop(int i);
void sprint(int i);
void quit(void);

int main(void) {

	printf("How Many Stacks? : ");
	scanf_s("%d", &n);

	top[0] = boundary[0] = 0;
	for (int i = 1; i < n; i++) {
		top[i] = boundary[i] = (MEMORY_SIZE / n) * i;
		
	}
	boundary[n] = MEMORY_SIZE;

	char* delimiter = " \n";
	char* context;
	char* op = NULL;
	element student;
	FILE* fp;
	fopen_s(&fp, "input.txt", "r");
	char line[MAX_LEN];

	printf("C Language program to implement the Multiple Stacks \n");
	printf("add stack_num(0-2) name : add 0 kim\n");
	printf("delete stack_num(0-2) : delete 0\n");
	printf("sprint stack_num(0-2) : sprint 0\n");
	printf("quit \n");
	printf("***************************************************\n\n");

	if (fp == NULL) {
		fprintf(stderr, "Cannot open this file");
		exit(EXIT_FAILURE);
	}

	int i;

	while (1) {
		if (!fgets(line, MAX_LEN, fp)) {
			break;
		}
		op = strtok_s(line, delimiter, &context);

		if (!strcmp(op, "add")) {
			sscanf_s(context, "%d %s", &i, &student.name, sizeof(student.name));
			if (i >= n) {
				printf("Stack number error, try again \n");
				continue;
			}
			push(i,student);
		}
		else if (!strcmp(op, "delete")) {
			sscanf_s(context, "%d", &i);
			if (i >= n) {
				printf("Stack number error, try again \n");
				continue;
			}
			student = pop(i);
		}
		else if (!strcmp(op, "sprint")) {
			sscanf_s(context, "%d", &i);
			if (i >= n) {
				printf("Stack number error, try again \n");
				continue;
			}
			sprint(i);
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
void stackFull(int i) {
	printf("Stack %d is Full \n", i);
}
void stackEmpty(void) {
	fprintf(stderr, "stack is empty, cannot show element to you\n");
	exit(EXIT_FAILURE);
}
void push(int i,element item) {
	if (top[i] == boundary[i + 1]) {
		stackFull(i);
	}
	else {
		memory[++top[i]] = item;
		printf("%s is pushed in Stack No. %d \n", item.name, i);
	}
}
element pop(int i) {
	if (top[i] == boundary[i]) {
		stackEmpty();
	}
	element item = memory[top[i]--];
	printf("%s is popped from Stack No. %d \n", item.name, i);
	return item;
}
void sprint(int i) {
	printf("\n");
	int reader = top[i];
	for (int j = reader; j > boundary[i]; j--) {
		printf("%s \n", memory[j].name);
	}
}
void quit(void) {
	printf("\nProgram end\n\n");
	for (int i = 0; i < n; i++) {
		printf("stack %d : \n", i);
		sprint(i);
		printf("\n");
	}

	exit(EXIT_SUCCESS);
}