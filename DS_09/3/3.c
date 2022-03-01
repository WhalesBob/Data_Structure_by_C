/*
3. ������ ���� ���ĵ��� �ʴ� ����(���� ������)�� input.txt ���Ͽ��� �Է·� �޾�
Circularly Linked List�� ����� ���� ���� ���� ����Ǵ� ���α׷��� �ۼ��϶�.

(1) ���� ����
�� �Է�����(��input.txt��)�� ���� �����͸� �Է¹����鼭 Circularly Linked List�� �����.
�� Circularly Linked List�� ó������ ������ ����� �����͸� ����Ѵ�. ��� ���� : (����ּ�, ������ �ʵ�, ��ũ��)
�� ������ Ȧ���� ��带 Circularly Linked List���� �����Ѵ�. 
�� Linked List�� ó������ ������ ����� �����͸� ����Ѵ�. ��� ���� : (����ּ�, ������ �ʵ�, ��ũ��)
�� Linked List�� ��� �����Ѵ�.

(2) ���� ���λ���
�� ����ü ���ǹ��� ������ ����.
typedef struct listNode *listPointer;
typedef struct listNode {
int data;
listPointer link;
} listNode;
listPointer first = NULL;
*/

#define MALLOC(p,s){\
	if(!((p) = malloc(s))){\
		fprintf(stderr, "Insufficient Memory");\
		exit(EXIT_FAILURE);\
	}\
}\

#include <stdio.h>
#include <stdlib.h>

typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
}listNode;

listPointer first = NULL;

void insertFront(listPointer* last, listPointer node);
void insertLast(listPointer* last, listPointer node);
void deleteList(listPointer* last);
void printList(listPointer * last);
void deleteAll(listPointer* last);

int main(void) {

	FILE* fp;
	fopen_s(&fp, "input.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "Cannot open input file \n");
		exit(EXIT_FAILURE);
	}

	listPointer* last = &first;

	while (!feof(fp)) {
		listPointer node;
		MALLOC(node, sizeof(*node));
		fscanf_s(fp, "%d ", &(*node).data);
		
		insertLast(last, node);
	}

	printList(last);

	deleteList(last);
	printf("\n\nAfter deleting nodes with odd value \n\n");

	printList(last);

	deleteAll(last);
	
	return 0;
}
void insertFront(listPointer* last, listPointer node) {
	if (!(*last)) {
		*last = node;
		node->link = node;
	}
	else {
		node->link = (*last)->link;
		(*last)->link = node;
	}
}
void insertLast(listPointer* last, listPointer node) {
	if (!(*last)) {
		*last = node;
		node->link = node;
	}
	else {
		node->link = (*last)->link;
		(*last)->link = node;
		(*last) = node;
	}
}
void deleteList(listPointer* last) {
	listPointer reader = (*last);
	for (; reader->link != (*last); reader = reader->link) {
		if ((reader->link->data) % 2 == 1) {
			listPointer deletePoint = reader->link;
			reader->link = reader->link->link;
			free(deletePoint);
		}
	}
	if (((*last)->data) % 2 == 1) { // last�� ������.
		listPointer deletePoint = (*last); // (���⼭ last�� ������. last�� �ٸ� �ʿ���  �����. reader->link �� (*last) ��)
		reader->link = reader->link->link;
		(*last) = reader;
		free(deletePoint);
	}
}
void printList(listPointer* last){
	printf("The Circularly LInked List contains : \n");

	listPointer reader = (*last)->link;
	int count = 0;
	for (; reader != (*last); reader = reader->link,count++) {
		printf("(%p,%5d, %p)", reader, reader->data, reader->link);
		if (count % 3 == 2) {
			printf("\n");
		}
	}
	printf("(%p,%5d, %p)", reader, reader->data, reader->link);
}
void deleteAll(listPointer* last) {
	while ((*last)->link != (*last)) {
		listPointer deletePoint = (*last)->link;
		(*last)->link = (*last)->link->link;
		free(deletePoint);
	}
	free((*last));
}