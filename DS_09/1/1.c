/*
1. [Linked Stacks] 다음과 같이 과목별 스택을 생성하고 실행의 예와 같이 처리하는 프로그램을 작성하라.
(1) 실행 순서
① 각 학반에 대한 교과목별 성적 데이터가 input.txt 파일에 저장되어 있다. input.txt 파일
의 각 라인은 (과목번호, 학반, 성적)에 대한 정보로 구성되어 있으며, 각 라인들은 학반에 대하여 정렬되어 있다.
입력파일(“input.txt”)의 데이터 순서대로 각 과목 별로 해당 교과목 Linked Stack에 저장 하시오. (과목이 3개이므로 3개의 스택이 필요함)
② 각 과목 별 해당 스택으로부터 데이터를 하나씩 pop하여 아래와 같이 출력하시오.
*/

#define MALLOC(p,s){\
	if(!((p) = malloc(s))){\
		fprintf(stderr, "Insufficient Memory");\
		exit(EXIT_FAILURE);\
	}\
}\

#include <stdio.h>
#include <stdlib.h>

#define MAX_STACKS 3

typedef struct {
	int classNumber;
	int score;
}element;

typedef struct stack* stackPointer;
typedef struct stack {
	element data;
	stackPointer link;
}listNode;

stackPointer top[MAX_STACKS];

void stackEmpty(void);
void push(int i, element item);
element pop(int i);
void printStack(int n);

int main(void) {

	FILE* fp;
	fopen_s(&fp, "input.txt", "r");
	if (fp == NULL) {
		fprintf(stderr,"Cannot open input file \n");
		exit(EXIT_FAILURE);
	}

	int lectureNumber;

	while (!feof(fp)) {
		element item;
		fscanf_s(fp, "%d %d %d\n", &lectureNumber, &item.classNumber, &item.score);
		push(lectureNumber, item);
	}

	printf("node 주소, 과목번호, 학반, 성적,    link \n");
	for (int i = 0; i < MAX_STACKS; i++) {
		printStack(i);
	}

	return 0;
}
void stackEmpty(void) {
	printf("Stack is Empty \n");
}
void push(int i, element item) {
	stackPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = item;
	temp->link = top[i];
	top[i] = temp;
}
element pop(int i) {
	element item;
	stackPointer temp = top[i];
	if (!temp) {
		stackEmpty();
	}
	item = temp->data;
	top[i] = temp->link;
	free(temp);
	return item;
}
void printStack(int n) {
	printf("*******************************************\n");
	stackPointer reader = top[n];
	for (; reader; reader = reader->link) {
		printf("%p %8d %7d %5d    %p \n", 
			reader, n, reader->data.classNumber, reader->data.score, reader->link);
	}
}
