/*
3. 다음과 같이 정렬되지 않는 점수(정수 데이터)를 input.txt 파일에서 입력력 받아
Circularly Linked List를 만들고 실행 예와 같이 수행되는 프로그램을 작성하라.

(1) 실행 순서
① 입력파일(“input.txt”)로 부터 데이터를 입력받으면서 Circularly Linked List를 만든다.
② Circularly Linked List의 처음부터 끝까지 노드의 데이터를 출력한다. 출력 형태 : (노드주소, 데이터 필드, 링크값)
③ 성적이 홀수인 노드를 Circularly Linked List에서 삭제한다. 
④ Linked List의 처음부터 끝까지 노드의 데이터를 출력한다. 출력 형태 : (노드주소, 데이터 필드, 링크값)
⑤ Linked List를 모두 삭제한다.

(2) 구현 세부사항
① 구조체 정의문은 다음과 같다.
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
	if (((*last)->data) % 2 == 1) { // last의 데이터.
		listPointer deletePoint = (*last); // (여기서 last가 없어짐. last를 다른 쪽에다  줘야지. reader->link 가 (*last) 임)
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