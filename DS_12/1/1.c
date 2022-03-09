/*
1. [����Ʈ��] ������ ���� Ʈ���� �����ϰ� ����Ʈ�� ��ȸ��� �� ������ȸ(inorder traversal),
������ȸ(preorder traversal), ������ȸ(postorder traversal)�� ���� ����ϴ� ���α׷��� �ۼ��϶�. 

�� ������ �׸��� ���� ����Ʈ���� �����Ѵ�. 
�� �����ʹ� �׸��� ���� A, B, C, D, E �� ����Ѵ�. 
�� ���������� ��带 ������ ��, �׸��� ���� ������ ����Ʈ���� �ǰ� ��ũ�� �����Ѵ�.
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

treePointer root = NULL;

treePointer createNode(char c);
void inorder(treePointer p);
void preOrder(treePointer p);
void postOrder(treePointer p);

int main(void) {

	treePointer a, b, c, d, e;
	a = createNode('A');
	b = createNode('B');
	c = createNode('C');
	d = createNode('D');
	e = createNode('E');

	a->leftChild = b;
	a->rightChild = c;
	b->leftChild = d;
	b->rightChild = e;

	root = a;

	printf("Creating a complete binary tree \n");
	printf("\nthree binary tree traversal ");
	
	printf("\nInorder traversal %5c ", ':');
	inorder(root);

	printf("\n\npreorder traversal %4c ", ':');
	preOrder(root);

	printf("\n\npostorder traversal %3c ", ':');
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
		printf("\n(%p : %p %c %p) ", p, p->leftChild, p->data, p->rightChild);
		inorder(p->rightChild);
	}
	
}
void preOrder(treePointer p) {
	if (p) {
		printf("\n(%p : %p %c %p) ", p, p->leftChild, p->data, p->rightChild);
		preOrder(p->leftChild);
		preOrder(p->rightChild);
	}
}
void postOrder(treePointer p) {
	if (p) {
		postOrder(p->leftChild);
		postOrder(p->rightChild);
		printf("\n(%p : %p %c %p) ", p, p->leftChild, p->data, p->rightChild);
	}
}
