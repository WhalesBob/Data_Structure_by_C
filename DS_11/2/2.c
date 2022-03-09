/*
2. ������ ���� ���� S�� ���Ͽ� ��ġ����(equivalence relation, ��) R�� �Ʒ��� ����. ��ġ����(equivalence relation, ��) 
R�� ����Ͽ� S�� ��ġ��(equivalence class)�� ���ϴ� ���α׷��� �ۼ��϶�.
��ġ����� ���Ḯ��Ʈ�� �̿��Ͽ� ǥ�� �Ѵ�. ��ġ���� ���ϱ� ���ؼ���
��ġ���� ���Ḯ��Ʈ�� �̿��Ͽ� ��ũ�� ����(Linked Stack)�� �����Ͽ��� �ϸ� ����� ����
���� ���ƾ� �Ѵ�. symetric ���踦 ��Ÿ���� linked list�� ���� ����ϰ�, �� ��ġ Ŭ������ ����Ѵ�.
��ġ Ŭ���� ��½� linked stack���� pop �� ������ ������ ��忡 ���� ������
������ ���� ���� ��� �Ͻÿ�. 

S = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}
R ���� 0��4, 3��1, 6��10, 8��9, 7��4, 6��8, 3��5, 2��11, 11��0����

(1) ���� ����
�� �����Է��� ���� ���� S�� ũ��� ��ġ���踦 ��Ÿ���� ������ �����͸� �Է¹����鼭 ��
������ symmetric ���迡 ���� linked list�� �Ʒ��� ���� ���� ��, ������ ���� ���� �����
��. ������ ù���� ���� �������ҿ� ���� ������ ��Ÿ����, ���� �� ���ʹ� equivalence
relation�� ��Ÿ����.
�� ��ġ���� ���Ͽ� ����Ѵ�. ��ġ�� ��½� ���ؿ��� pop�ϴ� ����� ������ �Բ� ����Ͻÿ�.
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
#define FALSE 0
#define TRUE 1

typedef struct node* nodePointer;
typedef struct node {
	int data;
	nodePointer link;
}node;

int main(void) {

	short int out[MAX_SIZE];
	nodePointer popWrite[MAX_SIZE];
	nodePointer seq[MAX_SIZE];
	nodePointer x, y, top;
	int i, j, n, w = 0;
	
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
		if (i == n - 1) {
			printf("%d ", i);
		}
		else {
			printf("%d, ", i);
		}
		out[i] = TRUE;
		seq[i] = NULL;
	}
	printf("} \n");
	printf("input pairs : ");

	while (!feof(fp)) {

		fscanf_s(fp, "%d %d\n", &i, &j);
		printf("%dR%d ", i, j);
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
		top = NULL;
		if (out[i]) {
			printf("\nNew Class : %5d", i);
			out[i] = FALSE;
			x = seq[i]; 
			for (;;) {
				while (x) {
					j = x->data;
					if (out[j]) {
						printf("%5d", j); out[j] = FALSE;
						y = x->link; x->link = top; top = x; x = y;
					}
					else {
						x = x->link;
					}
				}
				if (!top) {
					printf("\npop �� ��� ���� \n");
					for (int k = 0; k < w; k++) {
						printf("pop : (%p %4d %p) \n", popWrite[k], popWrite[k]->data, popWrite[k]->link);
					}
					w = 0;
					break;
				}
				popWrite[w++] = top;
				x = seq[top->data]; top = top->link;
			}
		}
		
	}
	printf("\n");
	return 0;
}