/*
1. [이진트리] 다음과 같은 트리를 생성하고 이진트리 순회방법 중 중위순회(inorder traversal),
전위순회(preorder traversal), 후위순회(postorder traversal)를 통해 출력하는 프로그램을 작성하라. 

① 다음과 그림과 같은 이진트리를 생성한다. 
※ 데이터는 그림과 같이 A, B, C, D, E 를 사용한다. 
※ 개별적으로 노드를 생성한 후, 그림과 같은 형태의 이진트리가 되게 링크를 연결한다.
② 이진트리 중위순회를 통해 데이터를 출력한다. ※ inorder(root);
③ 이진트리 전위순회를 통해 데이터를 출력한다. ※ preorder(root);
④ 이진트리 후위순회를 통해 데이터를 출력한다. ※ postorder(root);
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
