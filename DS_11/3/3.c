/*
3. ������ ���� ���� �����͸� �Է��ϸ鼭 �������带 ���� ���߿���ȯ������Ʈ (doubly linked circular list)��
�� ����� ���� ���� ���� ����Ǵ� ���α׷��� �ۼ��϶�.

(1) ���� ����
�� �Է�����(��input.txt��)�� ���� �����͸� �Է¹޴� ������� ����ȯ�����Ḯ��Ʈ�� ������ ���� �߰� �ǵ��� �Ѵ�.
�� ������� ���������� ����� ������ ������ ���� ���� ����Ѵ�. (forward & backward )
�� ������ 50�� ������ ��带 �����Ѵ�. 
�� ������� ���������� ����� �����͸� ������ ���� ���� ����Ѵ�. 
�� ��带 �����Ѵ�.
*/

#define MALLOC(p,s){\
	if(!((p) = malloc(s))){\
		fprintf(stderr,"Insufficient Memory. \n");\
		exit(EXIT_FAILURE);\
	}\
}\

#include <stdio.h>
#include <stdlib.h>

typedef struct node* nodePointer;
typedef struct node {
	nodePointer leftLink;
	int data; 
	nodePointer rightLink;
}node;

nodePointer header = NULL;

nodePointer create(int n);
void insert(nodePointer* node, nodePointer* newNode);
void ddelete(nodePointer node, nodePointer deleted);
void printDoubleList(void);

int main(void) {

	FILE* fp;
	fopen_s(&fp, "input.txt", "r");

	if (fp == NULL) {
		fprintf(stderr, "Cannot open input file. \n");
		exit(EXIT_FAILURE);
	}

	MALLOC(header, sizeof(*header));

	int n;
	fscanf_s(fp, "%d ", &n);
	nodePointer node = create(n);
	header->leftLink = node;
	header->rightLink = node;
	node->leftLink = header;
	node->rightLink = header;

	while (!feof(fp)) {

		fscanf_s(fp, "%d ", &n);
		nodePointer newNode = create(n);
		insert(&node, &newNode);
	}

	printDoubleList();
	
	nodePointer reader = header;

	do {
		nodePointer del = reader->rightLink;
		if ((del->data) <= 50) {
			ddelete(reader, del);
		}
		else {
			reader = reader->rightLink;
		}
	} while ((reader->rightLink) != header);

	printf("\nAfter deleting numbers less than and equal to 50 : \n");
	printDoubleList();

	printf("\n");
	return 0;
}
nodePointer create(int n) {
	nodePointer newNode;
	MALLOC(newNode, sizeof(*newNode));
	newNode->data = n;
	newNode->leftLink = NULL; newNode->rightLink = NULL;
}
void insert(nodePointer* node, nodePointer* newNode) {
	(*newNode)->leftLink = *node;
	(*newNode)->rightLink = (*node)->rightLink;
	(*node)->rightLink->leftLink = *newNode;
	(*node)->rightLink = *newNode;
	(*node) = (*newNode);
}
void ddelete(nodePointer node, nodePointer deleted) {
	if (node == deleted) {
		printf("Deletion of header node is not permitted. \n");
	}
	else {
		deleted->leftLink->rightLink = deleted->rightLink;
		deleted->rightLink->leftLink = deleted->leftLink;
		free(deleted);
	}
}
void printDoubleList(void) {
	int count = 0;

	nodePointer reader = header->rightLink;
	printf("forward \n");
	do {
		printf("(%p %4d  %p)   ", reader->leftLink, reader->data, reader->rightLink);
		if (count++ % 4 == 3) {
			printf("\n");
		}
		reader = reader->rightLink;
	} while (reader != header);

	count = 0;
	printf("\nbackward \n");
	reader = header->leftLink;
	do {
		printf("(%p %4d  %p)   ", reader->leftLink, reader->data, reader->rightLink);
		if (count++ % 4 == 3) {
			printf("\n");
		}
		reader = reader->leftLink;
	} while (reader != header);
}