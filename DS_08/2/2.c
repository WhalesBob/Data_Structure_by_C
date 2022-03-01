/*
2. �� 1�� ������ ������ �ҽ��� ������ ���� ����ü ���Ǹ� ����ϴ� ���α׷����� �����϶�.
�������� 1���� ������ �����ؾ� �Ѵ�. ( listPointer ��� �ڷ����� �������� �ʰ� listNode ��� �ڷ����� ����Ͽ� ����)

(1) ���� ����
�� �Է�����(��input.txt��)�� ���� �����͸� �Է¹����鼭 ���ĵ� Linked List�� �����. �Է� �����ʹ� ���ĵ��� ���� ������ �ߺ� �����ϴ�.
�� Linked List�� ó������ ������ ����� �����͸� ����Ѵ�. ��� ���� : (����ּ�, ������ �ʵ�, ��ũ��)
�� ������ Ȧ���� ��带 Linked List���� �����Ѵ�. 
�� Linked List�� ó������ ������ ����� �����͸� ����Ѵ�. ��� ���� : (����ּ�, ������ �ʵ�, ��ũ��)
�� Linked List�� ��� �����Ѵ�.

(2) ����ü ����
typedef struct listNode {
int data;
struct listNode *link;
} listNode;
listNode *first = NULL; // or struct listNode *first = NULL
*/

#define MALLOC(p,s){\
	if(!((p) = malloc(s))){\
		fprintf(stderr,"Insufficient Memory");\
		exit(EXIT_FAILURE);\
	}\
}\

#include <stdio.h>
#include <stdlib.h>

typedef struct listNode{
	int data;
	struct listNode *link;
}listNode;

listNode *first = NULL;

listNode *create(int firstNum, int secondNum);
void insert(listNode *x, int k);
listNode* insertFirst(listNode* first, int k);
void insertLast(listNode* x, int k);
void printList(listNode* first);
void delete(listNode* first, listNode* trail, listNode* x);

int main(void) {

	FILE* fp;
	fopen_s(&fp, "input.txt", "r");

	if (fp == NULL) {
		fprintf(stderr, "Cannot open file");
		exit(EXIT_FAILURE);
	}

	listNode *x = NULL;
	int m, n;
	fscanf_s(fp, "%d %d ", &m, &n);
	first = create(m, n); // �̱����� ������ ������, ������. �ּҰ����� �� �� ����.

	x = first; // �̰͵� ���� �ּҰ����� ���� ��.

	while (!feof(fp)) {
		x = first;
		fscanf_s(fp, "%d ", &n);
		if (n < x->data) { // x�� �� ù �����ͺ��� ���� ���
			first = insertFirst(first, n);
			continue;
		}
		while (1) { // x�� ���������� ������. �߰� �κ�, x�� ��ũ�� NULL�� �ƴ� ���.
			if ((x->link != NULL) && (n <= x->link->data)) { // x�� �� ó�� �ͺ��ٴ� ũ����, �� ���� �ͺ��ٴ� ���� ���
				insert(x, n); // �߰��� ����
				break;
			}
			else {
				x = x->link;
			}
			if (x->link == NULL) {
				insertLast(x, n);
				break;
			}
		}
	}
	printList(first);

	first = insertFirst(first, 0);
	x = first;

	while (x->link != NULL) {
		if ((x->link->data) % 2 == 1) {
			delete(first, x, x->link);
		}
		else {
			x = x->link;
		}
	}

	first = first->link;

	printf("After deleting nodes with odd value \n\n");
	printList(first);

	free(fp);
	return 0;
}
listNode *create(int firstNum, int secondNum) {
	listNode * head, *second;

	MALLOC(head, sizeof(*head));
	MALLOC(second, sizeof(*second));

	second->link = NULL;
	second->data = secondNum;
	head->data = firstNum;
	head->link = second;

	return head;
}
void insert(listNode *x, int k) {
	listNode *temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = k;

	temp->link = x->link; // x���� n�� ũ��, ���� �ͺ��� n�� ���� ���, �߰��� ����
	x->link = temp;
}
void insertLast(listNode *x, int k) {
	listNode *temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = k;

	temp->link = NULL;
	x->link = temp;
}
listNode *insertFirst(listNode *first, int k) {
	listNode *temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = k;

	temp->link = first;

	return temp;
}

void printList(listNode *first) {
	int n = 0;
	listNode *reader = first;
	printf("The ordered list contains : \n");
	for (; reader; reader = reader->link) {
		printf("(%p,%4d,%p) ", reader, reader->data, reader->link);
		if (n++ % 3 == 2) {
			printf("\n");
		}
	}
	printf("\n");
}
void delete(listNode *first, listNode *trail, listNode *x) { // x �κ��� ����� ��.
	if (trail) {
		trail->link = x->link; // �̰Ŵ� �߰��ϰ� �� �ϰ� ����.
	}
	else {
		first = first->link;
	}
	free(x);
}