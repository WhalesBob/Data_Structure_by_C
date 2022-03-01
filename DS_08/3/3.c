/*
3. 다음과 같은 학생정보를 파일(input.txt)에서 입력 받아 연결 리스트를 만들어 출력하시오.
연결리스트 작성시 입력 파일의 데이터 순서와 동일하게 작성하시오. 또 이 연결 리스트에서
여자와 남자를 분리하여 2개의 연결리스트를 만들어서 출력 하시오. 
*/

#define MALLOC(p,s){\
	if(!((p) = malloc(s))){\
		fprintf(stderr,"Insufficient Memory");\
		exit(EXIT_FAILURE);\
	}\
}\

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listNode {
	char name[20];
	char belonging[20];
	char sex[10];
	struct listNode* link;
}listNode;

listNode* first = NULL;

listNode* create(listNode* i, listNode* j);
listNode* insertFirst(listNode* first);
void insertLast(listNode* x, listNode newNode);
void printList(listNode* first);

int main(void) {

	FILE* fp;
	fopen_s(&fp, "input.txt", "r");

	if (fp == NULL) {
		fprintf(stderr, "Cannot open file");
		exit(EXIT_FAILURE);
	}

	listNode *x = NULL;
	listNode a, b;

	fscanf_s(fp, "%s %s %s\n", a.name, sizeof(a.name), a.belonging, sizeof(a.belonging), a.sex, sizeof(a.sex));
	fscanf_s(fp, "%s %s %s\n", b.name, sizeof(b.name), b.belonging, sizeof(b.belonging), b.sex, sizeof(b.sex));

	first = create(&a, &b); // 잘 create 된 것이다.
	x = first->link;

	while (!feof(fp)) {
		listNode node;
		fscanf_s(fp, "%s %s %s\n", node.name, sizeof(node.name), node.belonging, sizeof(node.belonging), node.sex, sizeof(node.sex));
		insertLast(x, node);
		x = x->link;
	}	
	printf("전체 리스트 : \n");
	printList(first);

	x = first; // 기존 first
	listNode* z = insertFirst(first); // 여자
	listNode* y = insertFirst(first); // 남자

	listNode* man = y;
	listNode* woman = z;

	while (x != NULL) {
		
		if (!strcmp(x->sex, "남자")) {
			man->link = x;
			man = man->link; // 남자 커서 옮겨감.

		}
		else {
			woman->link = x;
			woman = woman->link; // 여자 커서 옮겨감

		}
		x = x->link;
	}
	if (man->link != NULL && !strcmp(man->link->sex, "여자")) {
		man->link = NULL;
	}
	if (woman->link != NULL && !strcmp(woman->link->sex, "남자")) {
		woman->link = NULL;
	}
	printf("남자 리스트 : \n");
	printList(y->link);

	printf("\n여자 리스트 : \n");
	printList(z->link);

	free(fp);

	return 0;
}
listNode* create(listNode *i, listNode *j) {
	listNode *head, *second;

	MALLOC(head, sizeof(*head));
	MALLOC(second, sizeof(*second));

	strcpy_s(second->name, sizeof(second->name), j->name);
	strcpy_s(second->belonging, sizeof(second->belonging), j->belonging);
	strcpy_s(second->sex, sizeof(second->sex), j->sex);
	second->link = NULL;

	strcpy_s(head->name, sizeof(head->name), i->name);
	strcpy_s(head->belonging, sizeof(head->belonging), i->belonging);
	strcpy_s(head->sex, sizeof(head->sex), i->sex);
	head->link = second;

	return head;
}
listNode* insertFirst(listNode* first) {
	listNode* temp;
	MALLOC(temp, sizeof(*temp));
	strcpy_s(temp->name, sizeof(temp->name), "a");
	strcpy_s(temp->belonging, sizeof(temp->belonging), "aa");
	strcpy_s(temp->sex, sizeof(temp->sex), "aaa");

	temp->link = first;

	return temp;
}
void insertLast(listNode* x, listNode newNode) {
	listNode* temp;
	MALLOC(temp, sizeof(*temp));
	strcpy_s(temp->name, sizeof(temp->name), newNode.name);
	strcpy_s(temp->belonging, sizeof(temp->belonging), newNode.belonging);
	strcpy_s(temp->sex, sizeof(temp->sex), newNode.sex);

	temp->link = NULL;
	x->link = temp;
}
void printList(listNode* first) {
	int n = 0;
	listNode* reader = first;
	for (; reader; reader = reader->link) {
		printf("(%p, %s, %s, %s, %p) ", reader, reader->name, reader->belonging, reader->sex, reader->link);
		if (n++ % 2 == 1) {
			printf("\n");
		}
	}
	printf("\n");
}