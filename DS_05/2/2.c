/*
2. [ �����Ҵ� �迭�� �̿��� ����ť(linear queue) ] ������ ���� ���� ť�� �����ϰ�, ���� ���� ���� ����Ǵ� ���α׷��� �ۼ��϶�. 
ť�� full�̸� ť�� full �޽����� ����ϰ�, ť���� �����͸� �̵��ؾ� �� ��� ��data shift���޼����� ����ؾ� ��.
�׸��� empty�� �� �����͸� �����ϸ� Queue empty �޽����� ����ϰ� ������.
�߸��� ��ɿ� ���Ͽ��� �޽��� ������ ��� �ؾ� ��. 
ť�� ���� ����� input.txt ���Ͽ� ������, ť�ȿ� ������ ������ �л��� ���� �����̰�, ť�� ũ��� 3�̴�.

[ť ����]
#define MAX_QUEUE_SIZE 3

typedef struct {
int id; // unique id
char name[MAX_NAME_SIZE]; //last name
} element;

element queue[MAX_QUEUE_SIZE];

ť ó�� ���
add id name // queue�� ������ ����, ť�� full�̸� full �޽����� ����ϰ�, ť ����
�����͸� �̵��ؾ� �� ��� ��data shift���޼����� ����ؾ� ��. delete // queue�� ������ ����, empty�� �� �����͸� �����ϸ� Queue empty
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
int rear = -1;
int front = -1;

void queueFull(void);
void queueEmpty(void);
void addQ(element item);
element deleteQ(void);
void qprint(void);
void quit(void);

int main(void) {

	char* delimiter = " \n";
	char* context;
	char* op = NULL;
	element student;
	FILE* fp;
	fopen_s(&fp, "input.txt", "r");
	char line[MAX_LEN];

	printf("<<Sequencial queue operations where MAX_QUEUE_SIZE is 3>>\n");
	printf("add 1 Jung\n");
	printf("delete\n\n");
	printf("***************************************************\n\n");

	if (fp == NULL) {
		fprintf(stderr, "Cannot open this file");
		exit(EXIT_FAILURE);
	}

	while (1) {
		if (!fgets(line, MAX_LEN, fp)) {
			break;
		}
		op = strtok_s(line, delimiter, &context);

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
	fprintf(stderr, "queue is empty, cannot delete element\n");
	exit(EXIT_FAILURE);
}
void addQ(element item) {
	if ((rear == MAX_QUEUE_SIZE - 1) && front == -1) {
		queueFull();
	}else if ((rear == MAX_QUEUE_SIZE - 1) && front != -1) {
		for (int i = front + 1, j = 0; i <= rear; i++, j++) {
			queue[j] = queue[i];
		}
		rear = rear - front -1;
		front = -1;
		printf("data shift \n");
		queue[++rear] = item;
	}
	else {
		queue[++rear] = item;
	}
}
element deleteQ(void) {
	if (front == rear) {
		queueEmpty();
	}
	return queue[++front];
}
void qprint(void) {
	int reader = front + 1;
	for (int i = reader; i <= rear; i++) {
		printf("%d %s \n", queue[i].id, queue[i].name);
	}
}
void quit(void) {
	printf("Quit queue program\n");
	exit(EXIT_SUCCESS);
}
