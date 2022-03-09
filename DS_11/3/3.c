/*
3. 다음과 같이 정수 데이터를 입력하면서 “헤더노드를 가진 이중연결환형리스트 (doubly linked circular list)”
를 만들고 실행 예와 같이 수행되는 프로그램을 작성하라.

(1) 실행 순서
① 입력파일(“input.txt”)로 부터 데이터를 입력받는 순서대로 이중환형연결리스트의 마지막 노드로 추가 되도록 한다.
② 순방향과 역방향으로 노드의 정보를 실행의 예와 같이 출력한다. (forward & backward )
③ 성적이 50점 이하인 노드를 삭제한다. 
④ 순방향과 역방향으로 노드의 데이터를 실행의 예와 같이 출력한다. 
⑤ 노드를 삭제한다.
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