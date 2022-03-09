/*
1. 다음과 같이 집합 S에 대하여 동치관계(equivalence relation, ≡) R은 아래와 같다. 동치관계
(equivalence relation, ≡) R을 사용하여 S의 동치류(equivalence class)를 구하는 프로그램을 작성하라.
동치관계는 연결리스트를 이용하여 표현 한다. 동치류를 구하기 위해서는
배열로 스택을 구현하여야 하며 출력은 실행 예와 같아야 한다. 

S = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}
R ＝｛ 0≡4, 3≡1, 6≡10, 8≡9, 7≡4, 6≡8, 3≡5, 2≡11, 11≡0　｝

(1) 실행 순서
① 파일입력을 통해 집합 S의 크기와 동치관계를 나타내는 순서쌍 데이터를 입력받으면서 각
원소의 symmetric 관계에 대한 linked list를 아래와 같이 만든 후, 실행의 예와 같이 출력한다. 
파일의 첫줄은 집합 구성 원소에 대한 정보를 나타내며, 다음 줄 부터는 equivalence
relation을 나타낸다.
② 동치류를 구하여 출력한다.
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

	printf("\n\nsymemetric 관계 linked List \n");

	for (i = 0; i < n; i++) {
		nodePointer reader = seq[i];
		printf("%d : symmetric 관계 : \n", i);
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