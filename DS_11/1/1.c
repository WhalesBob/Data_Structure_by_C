/*
1. ������ ���� ���� S�� ���Ͽ� ��ġ����(equivalence relation, ��) R�� �Ʒ��� ����. ��ġ����
(equivalence relation, ��) R�� ����Ͽ� S�� ��ġ��(equivalence class)�� ���ϴ� ���α׷��� �ۼ��϶�.
��ġ����� ���Ḯ��Ʈ�� �̿��Ͽ� ǥ�� �Ѵ�. ��ġ���� ���ϱ� ���ؼ���
�迭�� ������ �����Ͽ��� �ϸ� ����� ���� ���� ���ƾ� �Ѵ�. 

S = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}
R ���� 0��4, 3��1, 6��10, 8��9, 7��4, 6��8, 3��5, 2��11, 11��0����

(1) ���� ����
�� �����Է��� ���� ���� S�� ũ��� ��ġ���踦 ��Ÿ���� ������ �����͸� �Է¹����鼭 ��
������ symmetric ���迡 ���� linked list�� �Ʒ��� ���� ���� ��, ������ ���� ���� ����Ѵ�. 
������ ù���� ���� ���� ���ҿ� ���� ������ ��Ÿ����, ���� �� ���ʹ� equivalence
relation�� ��Ÿ����.
�� ��ġ���� ���Ͽ� ����Ѵ�.
*/

#define MALLOC(p,s){\
	if(!((p) = malloc(s))){\
		fprintf(stderr,"Insufficient memory \n");\
		exit(EXIT_FAILURE);\
	}\
}\

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 24
#define MAX_STACK_SIZE 100
#define FALSE 0
#define TRUE 1
int top = -1;

typedef struct node* nodePointer;
typedef struct node {
	int data;
	nodePointer link;
}node;

int STACK[MAX_STACK_SIZE];

void push(int n);
int pop(void);

int main(void) {

	short int out[MAX_SIZE];
	nodePointer seq[MAX_SIZE];
	nodePointer x, y;
	int i,j,n;

	FILE* fp;
	fopen_s(&fp, "input.txt", "r");

	if (fp == NULL) {
		fprintf(stderr, "Cannot open input file. \n");
		exit(EXIT_FAILURE);
	}

	fscanf_s(fp, "%d\n", &n);

	printf("/* MAX_SIZE of a set S : %d */\n", MAX_SIZE);
	printf("current size of S : %d \n", n);
	printf(" S = { ");
	for (i = 0; i < n; i++) {
		if (i == n-1) {
			printf("%d ",i);
		}
		else {
			printf("%d, ",i);
		}
		out[i] = TRUE;
		seq[i] = NULL;
	}
	printf("} \n");
	printf("input pairs : ");

	while (!feof(fp)) {
		
		fscanf_s(fp, "%d %d\n", &i, &j);
		printf("%dR%d ",i,j);
		MALLOC(x, sizeof(*x));
		x->data = j; x->link = seq[i]; seq[i] = x;
		MALLOC(x, sizeof(*x));
		x->data = i; x->link = seq[j]; seq[j] = x;
	}

	printf("\n\nsymemetric ���� linked List \n");

	for (i = 0; i < n; i++) {
		nodePointer reader = seq[i];
		printf("%d : symmetric ���� : \n", i);
		while (reader != NULL) {
			printf("(%p %d %p)   ", reader, reader->data, reader->link);
			reader = reader->link;
		}
		printf("\n");
	}

	for (i = 0; i < n; i++) {
		if (out[i] == TRUE) {
			printf("\nNew Class : %5d", i);
			out[i] = FALSE;
			x = seq[i]; top = -1;
			for (;;) {
				while (x) {
					j = x->data;
					if (out[j]) {
						printf("%5d", j); out[j] = FALSE;
						push(j);
						x = x->link;
					}
					else {
						x = x->link;
					}
				}
				if (top == -1) {
					break;
				}
				x = seq[pop()];
			}
		}
	}
	printf("\n");
	return 0;
}
void push(int n) {
	STACK[++top] = n;
}
int pop(void) {
	return STACK[top--];
}