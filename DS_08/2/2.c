/*
2. 위 1번 문제를 구현한 소스를 다음과 같은 구조체 정의를 사용하는 프로그램으로 수정하라.
실행결과는 1번과 완전히 동일해야 한다. ( listPointer 라는 자료형을 정의하지 않고 listNode 라는 자료형을 사용하여 구현)

(1) 실행 순서
① 입력파일(“input.txt”)로 부터 데이터를 입력받으면서 정렬된 Linked List를 만든다. 입력 데이터는 정렬되지 않은 값으로 중복 가능하다.
② Linked List의 처음부터 끝까지 노드의 데이터를 출력한다. 출력 형태 : (노드주소, 데이터 필드, 링크값)
③ 성적이 홀수인 노드를 Linked List에서 삭제한다. 
④ Linked List의 처음부터 끝까지 노드의 데이터를 출력한다. 출력 형태 : (노드주소, 데이터 필드, 링크값)
⑤ Linked List를 모두 삭제한다.

(2) 구조체 정의
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
	first = create(m, n); // 이까지는 같지는 않지만, 오케이. 주소값으로 들어갈 수 있음.

	x = first; // 이것도 최초 주소값으로 들어가면 됨.

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

	temp->link = x->link; // x보다 n이 크고, 다음 것보다 n이 작을 경우, 중간에 끼움
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
void delete(listNode *first, listNode *trail, listNode *x) { // x 부분을 지우는 것.
	if (trail) {
		trail->link = x->link; // 이거는 중간하고 뒤 하고 통함.
	}
	else {
		first = first->link;
	}
	free(x);
}