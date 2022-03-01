/*
3. [ ȯ��ť(circular queue) ] 2�� ������ ���α׷��� ȯ��ť ���α׷����� �����϶�.

[�ڷ����� �Լ��� ����]

#define MAX_QUEUE_SIZE 3
#define MAX_NAME_SIZE 20
typedef struct {
int id; // unique id
char name[MAX_NAME_SIZE]; // last name
}element;
element queue[MAX_QUEUE_SIZE];
int rear, front;

[ť ����]
#define MAX_QUEUE_SIZE 3
typedef struct {
int id; // unique id
char name[MAX_NAME_SIZE]; //last name
} element;
element queue[MAX_QUEUE_SIZE];

ť ó�� ���
add id name // queue�� ������ ����, ť�� full�̸� ť�� full �޽����� ����ϰ�, ����
�Ͱ� ť�� ���Ե��� �ʾҴٴ� �޽����� �����. delete // queue�� ������ ����, empty�� �� �����͸� �����ϸ� Queue empty
�޽����� ����ϰ� ������. qprint // queue�� ������ ����Ʈ
quit // ���α׷� ���� ����
�߸��� ��ɾ� // �޽��� ������ ���
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 3
#define	MAX_NAME_SIZE 100
#define MAX_LEN 100

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
}element;

element queue[MAX_QUEUE_SIZE];
int rear = 0;
int front = 0;

void queueFull(void);
void queueEmpty(void);
void addQ(element item);
element deleteQ(void);
void qprint(void);
void quit(void);
int isFull(int a, int b);

int main(void) {

	char* delimiter = " \n";
	char* context;
	char* op = NULL;
	element student;
	FILE* fp;
	fopen_s(&fp, "input.txt", "r");
	char line[MAX_LEN];

	printf("<<Circular queue operations where MAX_QUEUE_SIZE is 3>>\n");
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
			sscanf_s(context, "%d %s", &student.id, &student.name, sizeof(student.name));
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
void queueFull(void) {
	printf("queue is full, not added\n");
}
void queueEmpty(void) {
	fprintf(stderr, "queue is empty \n");
	exit(EXIT_FAILURE);
}
void addQ(element item) {
	
	rear = (rear + 1) % MAX_QUEUE_SIZE;
//	printf("front : %d, rear : %d \n", front, rear);

	if (isFull(front,rear)) {
		queueFull();
	}
	else {
		queue[rear] = item;
	}


//	qprint();
	
}
element deleteQ(void) {
	
	if (front == rear) {
		queueEmpty();
	}
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];
}
void qprint(void) {
	int reader = front;
	while (reader != rear) {
		reader = (reader + 1) % MAX_QUEUE_SIZE;
		printf("%d, %s \n", queue[reader].id, queue[reader].name);
	}
}
void quit(void) {
	printf("Quit queue program\n");
	exit(EXIT_SUCCESS);
}
int isFull(int a, int b) {

	if (a == b) {
		rear--;
		if (rear == -1) {
			rear = MAX_QUEUE_SIZE - 1;
		}
		return 1;
	}
	else {
		return 0;
	}
}