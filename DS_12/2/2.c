/*
2. [ť�� �̿��� ��������Ʈ�� ����] �����Է��� �޾� ������ ���� ��������Ʈ��(complete binary tree)�� �����Ͽ�, 
����Ʈ�� ��ȸ��� �� ������ȸ, ������ȸ, ������ȸ�� ���� ����ϴ� ���α׷��� �ۼ��϶�.

(1) �������
�� �Է�����(input.txt)�κ��� ������ ���� ��������Ʈ���� �����Ѵ�
�� ����Ʈ�� ������ȸ�� ���� �����͸� ����Ѵ�. �� inorder(root);
�� ����Ʈ�� ������ȸ�� ���� �����͸� ����Ѵ�. �� preorder(root);
�� ����Ʈ�� ������ȸ�� ���� �����͸� ����Ѵ�. �� postorder(root);
*/

#define MALLOC(p,s){\
	if(!((p) = malloc(s))){\
		fprintf(stderr,"Insufficient Memory. \n");\
		exit(EXIT_FAILURE);\
	}\
}\

#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode* treePointer;
typedef struct treeNode {
	treePointer leftChild, rightChild;
	char data;
}treeNode;

#define MAX_QUEUE_SIZE 100
int front = -1, rear = -1;

treePointer root = NULL;
treePointer queue[MAX_QUEUE_SIZE];

treePointer createNode(char c);
void inorder(treePointer p);
void preOrder(treePointer p);
void postOrder(treePointer p);
void enQueue(treePointer p);
treePointer deQueue(void);
void queueEmpty(void);
void queueFull(void);

int main(void) {

	FILE* fp;
	fopen_s(&fp, "input.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "Cannot open input file. \n");
		exit(EXIT_FAILURE);
	}

	treePointer node, parent;

	while (!feof(fp)) {
		char c;
		fscanf_s(fp, "%c", &c,sizeof(c));
		if (c == '\n') {
			break;
		}
		node = createNode(c);

		if (root == NULL) {
			root = node;
		}
		else {
			int reader = front + 1;
			parent = queue[reader];
			if (parent->leftChild && parent->rightChild) {
				deQueue();
				parent = queue[++reader];
			}
			if (parent->leftChild == NULL) {
				parent->leftChild = node;
			}
			else {
				parent->rightChild = node;
			}
		}
		enQueue(node);
	}

	printf("Creating a complete binary tree \n");
	printf("\nthree binary tree traversal ");

	printf("\nInorder traversal %5c ", ':');
	inorder(root);

	printf("\npreorder traversal %4c ", ':');
	preOrder(root);

	printf("\npostorder traversal %3c ", ':');
	postOrder(root);

	return 0;
}
treePointer createNode(char c) {
	treePointer newNode;
	MALLOC(newNode, sizeof(*newNode));
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;
	newNode->data = c;
}
void inorder(treePointer p) {
	if (p) {
		inorder(p->leftChild);
		printf("%c ", p->data);
		inorder(p->rightChild);
	}

}
void preOrder(treePointer p) {
	if (p) {
		printf("%c ", p->data);
		preOrder(p->leftChild);
		preOrder(p->rightChild);
	}
}
void postOrder(treePointer p) {
	if (p) {
		postOrder(p->leftChild);
		postOrder(p->rightChild);
		printf("%c ", p->data);
	}
}
void enQueue(treePointer p){
	if (rear == MAX_QUEUE_SIZE - 1) {
		queueFull();
	}
	queue[++rear] = p;
}
treePointer deQueue(void){
	if (front == rear) {
		queueEmpty();
	}
	treePointer p = queue[++front];
	return p;
}
void queueEmpty(void) {
	printf("Queue is Empty \n");
}
void queueFull(void){
	printf("Queue is Full \n");
}