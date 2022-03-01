/*
3. ������ ���� �л������� ����(input.txt)���� �Է� �޾� ���� ����Ʈ�� ����� ����Ͻÿ�.
���Ḯ��Ʈ �ۼ��� �Է� ������ ������ ������ �����ϰ� �ۼ��Ͻÿ�. �� �� ���� ����Ʈ����
���ڿ� ���ڸ� �и��Ͽ� 2���� ���Ḯ��Ʈ�� ���� ��� �Ͻÿ�. 
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

	first = create(&a, &b); // �� create �� ���̴�.
	x = first->link;

	while (!feof(fp)) {
		listNode node;
		fscanf_s(fp, "%s %s %s\n", node.name, sizeof(node.name), node.belonging, sizeof(node.belonging), node.sex, sizeof(node.sex));
		insertLast(x, node);
		x = x->link;
	}	
	printf("��ü ����Ʈ : \n");
	printList(first);

	x = first; // ���� first
	listNode* z = insertFirst(first); // ����
	listNode* y = insertFirst(first); // ����

	listNode* man = y;
	listNode* woman = z;

	while (x != NULL) {
		
		if (!strcmp(x->sex, "����")) {
			man->link = x;
			man = man->link; // ���� Ŀ�� �Űܰ�.

		}
		else {
			woman->link = x;
			woman = woman->link; // ���� Ŀ�� �Űܰ�

		}
		x = x->link;
	}
	if (man->link != NULL && !strcmp(man->link->sex, "����")) {
		man->link = NULL;
	}
	if (woman->link != NULL && !strcmp(woman->link->sex, "����")) {
		woman->link = NULL;
	}
	printf("���� ����Ʈ : \n");
	printList(y->link);

	printf("\n���� ����Ʈ : \n");
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