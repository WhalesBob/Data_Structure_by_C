#define MALLOC(p,s){\
	if(!((p) = malloc(s))){\
		fprintf(stderr, "Insufficient Memory");\
		exit(EXIT_FAILURE);\
	}\
}\

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUES 3

typedef struct {
	int classNumber;
	int score;
}element;

typedef struct queue* queuePointer;
typedef struct queue {
	element data;
	queuePointer link;
}queue;

queuePointer front[MAX_QUEUES], rear[MAX_QUEUES];

void queueEmpty(void);
void addQ(int i, element item);
element deleteQ(int i);
void printQueue(int n);

int main(void) {

	FILE* fp;
	fopen_s(&fp, "input.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "Cannot open input file \n");
		exit(EXIT_FAILURE);
	}

	int lectureNumber;
	while (!feof(fp)) {
		element item;
		fscanf_s(fp, "%d %d %d\n", &lectureNumber, &item.classNumber, &item.score);
		addQ(lectureNumber, item);
	}

	printf("node 林家, 苞格锅龋, 切馆, 己利,    link \n");
	for (int i = 0; i < MAX_QUEUES; i++) {
		printQueue(i);
	}

	return 0;
}
void queueEmpty(void) {
	printf("Queue is empty \n");
}
void addQ(int i, element item) {
	queuePointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = item;
	temp->link = NULL;
	if (front[i]) {
		rear[i]->link = temp;
	}
	else {
		front[i] = temp;
	}
	rear[i] = temp;
}
element deleteQ(int i) {
	element item;
	queuePointer temp = front[i];
	if (!temp) {
		queueEmpty();
	}
	item = temp->data;
	front[i] = temp->link;
	free(temp);
	return item;
}
void printQueue(int n) {
	printf("*******************************************\n");
	queuePointer reader = front[n];
	for (; reader; reader = reader->link) {
		printf("%p %8d %7d %5d    %p \n",
			reader, n, reader->data.classNumber, reader->data.score, reader->link);
	}
}