/*
1. [ 동적할당배열을 이용한 환형큐(circular queue) ] 동적할당 배열을 이용한 환형큐를 생성하고 실행 예와 같이 수행되는 프로그램을 작성하라. 
queueFull이 발생하면 queue capacity를 두 배로 확장한다.
단 초기의 환형큐의 크기는 2이며, 환형큐 안의 element는 구조체이며 2개의 필드(id, name)로 구성되어 있다.
큐에 대한 명령은 input.txt 파일에 있으며, 큐안에 저장할 내용은 학생에 대한 정보이다.

큐 처리 명령

add id name // queue에 데이터 삽입, 큐가 full이면 full 메시지를 출력하고, queue
capacity를 두 배로 확장한 후 데이터를 삽입
delete // queue에 데이터 삭제, empty일 때 데이터를 삭제하면 Queue empty
메시지를 출력하고 종료함. qprint // queue의 내용을 프린트
quit // 프로그램 수행 종료, 수행 종료 메시지 출력
잘못된 명령어 // 메시지 오류를 출력

*/

#define MALLOC(p,s){\
	if(!((p) = malloc(s))){\
		fprintf(stderr,"Insufficient Memory");\
		exit(EXIT_FAILURE);\
	}\
}\

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	MAX_NAME_SIZE 100
#define MAX_LEN 100

int rear = 0;
int front = 0;
int capacity = 2;

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
}element;

element* queue = NULL; // 이게 바뀜으로써 추가적으로 바뀌어야 하는 것들이 무조건 있음.

void copy(int start, int end, element* newQueue);

void queueFull(element item);
void queueEmpty(void);
void addQ(element item);
element deleteQ(void);
void qprint(void);
void quit(void);
int isFull(int a, int b);

int main(void) {

	MALLOC(queue, capacity * sizeof(queue)); // 이거 이래 줬으면, free도 찍어 줘야 한다. 명심할 것.

	char* delimiter = " \n";
	char* context;
	char* op = NULL;
	element student;
	FILE* fp;
	fopen_s(&fp, "input.txt", "r");
	char line[MAX_LEN];

	printf("<<Circular queue operations where the initial capacity is 2>>\n");
	printf("add 1 Jung\n");
	printf("delete\n\n");
	printf("***************************************************\n");

	if (fp == NULL) {
		fprintf(stderr, "Cannot open this file");
		exit(EXIT_FAILURE);
	}

	while (1) {
		if (!fgets(line, MAX_LEN, fp)) {
			break;
		}
		op = strtok_s(line, delimiter, &context); // 이까지 같음. 읽어들이는 과정

		if (!strcmp(op, "add")) {
			sscanf_s(context, "%d %s", &student.id, &student.name, sizeof(student.name)); // 잘 들어간 것은 FACT
			addQ(student);
		}
		else if (!strcmp(op, "delete")) {
			student = deleteQ();
		}
		else if (!strcmp(op, "qprint")) {
			qprint();
			printf("\n");
		}
		else if (!strcmp(op, "quit")) {
			quit();
		}
		else {
			printf("wrong command! try again!\n");
		}
	}
}
void queueFull(element item) {
	printf("Queue capacity is doubled \n");

	int start;
	element* newQueue = NULL;
	MALLOC(newQueue, 2 * capacity * sizeof(*queue));

	start = (front + 1) % capacity;
	if (start < 2) {
		copy(start, start + capacity - 1, newQueue);
	}
	else {
		copy(start, capacity, newQueue);
		copy(0, rear + 1, newQueue + capacity - start);
	}

	front = 2 * capacity - 1;
	rear = capacity - 2;
	capacity *= 2;
	free(queue);
	queue = newQueue;

	printf("current queue capacity is %d \n", capacity);
	queue[++rear] = item;

	qprint();
	printf("\n\n");
	
}
void queueEmpty(void) {
	fprintf(stderr, "queue is empty \n");
	exit(EXIT_FAILURE);
}
void addQ(element item) {

	rear = (rear + 1) % capacity;

	if (front == rear) {
		queueFull(item);
	}
	else {
		queue[rear] = item;
	}
}
element deleteQ(void) {

	if (front == rear) {
		queueEmpty();
	}
	front = (front + 1) % capacity;
	return queue[front];
}
void qprint(void) {
	int reader = front;
	while (reader != rear) {
		reader = (reader + 1) % capacity;
		printf("%d, %s \n", queue[reader].id, queue[reader].name); // 여기서 첫 부분에서는 잘못 가리킴.
	}
}
void quit(void) {
	printf("end of program! \n");
	exit(EXIT_SUCCESS);
}
int isFull(int a, int b) {

	if (a == b) {
		rear--;
		if (rear == -1) {
			rear = capacity - 1;
		}
		return 1;
	}
	else {
		return 0;
	}
}
void copy(int start, int end ,element* newQueue) { // 끝이 몇 개인지 설정해야 하네

	for (int i = 0, j = start; i < end - start; i++,j++) {
		newQueue[i] = queue[j];
	}
}