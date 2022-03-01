/*
1. 다음과 같이 정렬되지 않는 점수(정수 데이터)를 파일에서 입력 받아 정렬된 Linked List를 만들고 실행 예와 같이 수행되는 프로그램을 작성하라.

(1) 실행 순서
① 입력파일(“input.txt”)로 부터 데이터를 입력받으면서 정렬된 Linked List를 만든다. 입력 데이터는 정렬되지 않은 값으로 중복 가능하다.
② Linked List의 처음부터 끝까지 노드의 데이터를 출력한다. 출력 형태 : (노드주소, 데이터 필드, 링크값)
③ 성적이 홀수인 노드를 Linked List에서 삭제한다.
④ Linked List의 처음부터 끝까지 노드의 데이터를 출력한다. 출력 형태 : (노드주소, 데이터 필드, 링크값)
⑤ Linked List를 모두 삭제한다.

(2) 구조체 정의

typedef struct listNode *listPointer;
struct listNode {
int data;
listPointer link;
} listNode;
listPointer first = NULL;
*/

#define MALLOC(p,s){\
	if(!((p) = malloc(s))){\
		fprintf(stderr,"Insufficient Memory");\
		exit(EXIT_FAILURE);\
	}\
}\

#include <stdio.h>
#include <stdlib.h>

typedef struct listNode *listPointer;
struct listNode {
	int data;
	listPointer link;
}listNode;

listPointer first = NULL;

listPointer create(int firstNum, int secondNum);
void insert(listPointer x, int k);
listPointer insertFirst(listPointer first, int k);
void insertLast(listPointer x, int k);
void printList(listPointer first);
void delete(listPointer first, listPointer trail, listPointer x);

int main(void) {

	FILE* fp;
	fopen_s(&fp, "input.txt", "r");

	if (fp == NULL) {
		fprintf(stderr, "Cannot open file");
		exit(EXIT_FAILURE);
	}

	listPointer x = NULL;
	int m, n;
	fscanf_s(fp, "%d %d ", &m, &n);
	first = create(m, n);

	x = first;

	while (!feof(fp)) {
		x = first;
		fscanf_s(fp, "%d ", &n);
		if (n < x->data) { // x의 맨 첫 데이터보다 작을 경우
			first = insertFirst(first, n);
			continue;
		}
		while (1) { // x가 순차적으로 증가함. 중간 부분, x의 링크가 NULL이 아닐 경우.
			if ((x->link != NULL) && (n <= x->link->data)) { // x가 맨 처음 것보다는 크지만, 그 다음 것보다는 작을 경우
				insert(x, n); // 중간에 끼움
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
listPointer create(int firstNum, int secondNum) {
	listPointer head,second;

	MALLOC(head, sizeof(*head));
	MALLOC(second, sizeof(*second));
	
	second->link = NULL;
	second->data = secondNum;
	head->data = firstNum;
	head->link = second;

	return head;
}
void insert(listPointer x, int k) {
	listPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = k;
	
	temp->link = x->link; // x보다 n이 크고, 다음 것보다 n이 작을 경우, 중간에 끼움
	x->link = temp;
}
void insertLast(listPointer x, int k) {
	listPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = k;
	
	temp->link = NULL;
	x->link = temp;
}
listPointer insertFirst(listPointer first, int k) {
	listPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = k;

	temp->link = first;

	return temp;
}

void printList(listPointer first) {
	int n = 0;
	listPointer reader = first;
	printf("The ordered list contains : \n");
	for (; reader; reader = reader->link) {
		printf("(%p,%4d,%p) ", reader,reader->data,reader->link);
		if (n++ % 3 == 2) {
			printf("\n");
		}
	}
	printf("\n");
}
void delete(listPointer first,listPointer trail, listPointer x) { // x 부분을 지우는 것.
	if (trail) {
		trail->link = x->link; // 이거는 중간하고 뒤 하고 통함.
	}
	else {
		first = first->link;
	}
	free(x);
}