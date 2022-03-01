/*
2. [Linked Queues] 다음과 같이 과목별 큐를 생성하고 실행하는 프로그램을 작성하라.
(1) 실행 순서
① 각 학반에 대한 교과목별 성적 데이터가 input.txt 파일에 저장되어 있다. input.txt 파일
의 각 라인은 (과목번호, 학반, 성적)에 대한 정보로 구성되어 있으며, 각 라인들은 학반에 대하여 정렬되어 있다. 
입력파일(“input.txt”)로 부터 학반 순으로 미리 정렬된 데이터를 입력받으면서 순서대로, 해당 학반의 Linked Queue에 저장한다.
입력파일(“input.txt”)의 각 라인은(과목번호, 학년, 성적)에 대한 정보를 가지고 있다. 
② 해당 학반의 Linked Queue에서 데이터를 하나씩 꺼내어 아래와 같이 출력하라.
*/

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

	printf("node 주소, 과목번호, 학반, 성적,    link \n");
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