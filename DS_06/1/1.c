/*
1. [ �����Ҵ�迭�� �̿��� ȯ��ť(circular queue) ] �����Ҵ� �迭�� �̿��� ȯ��ť�� �����ϰ� ���� ���� ���� ����Ǵ� ���α׷��� �ۼ��϶�. 
queueFull�� �߻��ϸ� queue capacity�� �� ��� Ȯ���Ѵ�.
�� �ʱ��� ȯ��ť�� ũ��� 2�̸�, ȯ��ť ���� element�� ����ü�̸� 2���� �ʵ�(id, name)�� �����Ǿ� �ִ�.
ť�� ���� ����� input.txt ���Ͽ� ������, ť�ȿ� ������ ������ �л��� ���� �����̴�.

ť ó�� ���

add id name // queue�� ������ ����, ť�� full�̸� full �޽����� ����ϰ�, queue
capacity�� �� ��� Ȯ���� �� �����͸� ����
delete // queue�� ������ ����, empty�� �� �����͸� �����ϸ� Queue empty
�޽����� ����ϰ� ������. qprint // queue�� ������ ����Ʈ
quit // ���α׷� ���� ����, ���� ���� �޽��� ���
�߸��� ��ɾ� // �޽��� ������ ���

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

element* queue = NULL; // �̰� �ٲ����ν� �߰������� �ٲ��� �ϴ� �͵��� ������ ����.

void copy(int start, int end, element* newQueue);

void queueFull(element item);
void queueEmpty(void);
void addQ(element item);
element deleteQ(void);
void qprint(void);
void quit(void);
int isFull(int a, int b);

int main(void) {

	MALLOC(queue, capacity * sizeof(queue)); // �̰� �̷� ������, free�� ��� ��� �Ѵ�. ����� ��.

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
		op = strtok_s(line, delimiter, &context); // �̱��� ����. �о���̴� ����

		if (!strcmp(op, "add")) {
			sscanf_s(context, "%d %s", &student.id, &student.name, sizeof(student.name)); // �� �� ���� FACT
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
		printf("%d, %s \n", queue[reader].id, queue[reader].name); // ���⼭ ù �κп����� �߸� ����Ŵ.
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
void copy(int start, int end ,element* newQueue) { // ���� �� ������ �����ؾ� �ϳ�

	for (int i = 0, j = start; i < end - start; i++,j++) {
		newQueue[i] = queue[j];
	}
}