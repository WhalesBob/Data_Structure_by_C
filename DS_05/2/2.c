/*
2. [ 정적할당 배열을 이용한 선형큐(linear queue) ] 다음과 같은 선형 큐를 생성하고, 실행 예와 같이 수행되는 프로그램을 작성하라. 
큐가 full이면 큐가 full 메시지를 출력하고, 큐안의 데이터를 이동해야 할 경우 “data shift”메세지를 출력해야 함.
그리고 empty일 때 데이터를 삭제하면 Queue empty 메시지를 출력하고 종료함.
잘못된 명령에 대하여는 메시지 오류를 출력 해야 함. 
큐에 대한 명령은 input.txt 파일에 있으며, 큐안에 저장할 내용은 학생에 대한 정보이고, 큐의 크기는 3이다.

[큐 정의]
#define MAX_QUEUE_SIZE 3

typedef struct {
int id; // unique id
char name[MAX_NAME_SIZE]; //last name
} element;

element queue[MAX_QUEUE_SIZE];

큐 처리 명령
add id name // queue에 데이터 삽입, 큐가 full이면 full 메시지를 출력하고, 큐 안의
데이터를 이동해야 할 경우 “data shift”메세지를 출력해야 함. delete // queue에 데이터 삭제, empty일 때 데이터를 삭제하면 Queue empty
메시지를 출력하고 종료함. qprint // queue의 내용을 프린트
quit // 프로그램 수행 종료
잘못된 명령어 // 메시지 오류를 출력
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
