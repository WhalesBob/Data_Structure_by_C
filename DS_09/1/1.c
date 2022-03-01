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

	printf("node 林家, 苞格锅龋, 切馆, 己利,    link \n");
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
