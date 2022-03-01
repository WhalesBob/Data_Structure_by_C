/*
3. �� ���� arry�� ����Ͽ� multistack�� ���� ó���ϴ� ���α׷��� �ۼ��Ͻÿ�. �迭�� ũ��� 10�̸� �迭���� ���Ҵ� ��Ʈ������ ó���Ѵ�. 
������ ������ �Է��� �޾� ���Ѵ�. �� ������ ũ��� 10/(���ü�)�� �����ϰ� �Ѵ�.
�� ������ ������ ���Ҵ� �ٸ� ������ ���� ������ ���� �� �ִ�. ������ ��ȣ�� 0������ �����ϸ�, ������ ���� 3���̸� ���ù�ȣ�� 0, 1, 2 �� �ȴ�. 
���� ó�� ��ɾ�� input.txt ���Ͽ��� �Է� �޵��� �Ѵ�.

[���� ó�� ��ɾ�]
add ���ù�ȣ ��Ʈ�� : �ش� ���ÿ� ��Ʈ�� ����, full�̸� ���� full �޽��� ���
delete ���ù�ȣ : �ش� ���ÿ� ��Ʈ�� ����, empty�̸� ���� empty �޽��� ���
sprint ���ù�ȣ : �ش罺�þ��� top���� bottom ������ ���
quit : ���α׷� ���� ����. ���α׷� ���� �޽��� ����ϰ� ��� ������ ������
����Ѵ�. ��ɾ� ������ ��wrong command, try again!!�� �޽��� ���
���ù�ȣ ������ ��stack number error, try again�� �޽��� ���
������ ���� �����Ͽ� ���α׷��� �ۼ��� ��.

[���� ����]
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