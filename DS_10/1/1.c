#define MALLOC(p,s){\
	if (!((p) = malloc(s))) {\
		fprintf(stderr,"Insufficient Memory \n");\
		exit(EXIT_FAILURE);\
	}\
}\

#define COMPARE(x,y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

#include <stdio.h>
#include <stdlib.h>

typedef struct polyNode* polyPointer;

typedef struct polyNode {
	int coef;
	int expon;
	polyPointer link;
};

polyPointer a, b;

void makeWholeList(FILE* fp, polyPointer* p);
polyPointer create(int coefficient, int exponent);
void makeList(FILE* fp, char order, polyPointer* pointer);
polyPointer padd(polyPointer a, polyPointer b);
void attach(float coefficient, int exponent, polyPointer* pointer);
void printList(polyPointer p);
void deleteList(polyPointer* p);

int main(void) {

	FILE* fp1, *fp2;
	fopen_s(&fp1, "a.txt", "r");
	fopen_s(&fp2, "b.txt", "r");

	if (fp1 == NULL || fp2 == NULL) {
		fprintf(stderr, "Cannot open input a or b file");
		exit(EXIT_FAILURE);
	}

	makeWholeList(fp1, &a);
	printf("     a : \n");
	printList(a);

	makeWholeList(fp2, &b);
	printf("     b : \n");
	printList(b);

	polyPointer sum = padd(a, b);
	printf("a+b=c : \n");
	printList(sum);

	deleteList(&a); deleteList(&b); deleteList(&sum);
	
	return 0;
}
void makeWholeList(FILE* fp, polyPointer* p) {
	int m, n;
	char order;
	fscanf_s(fp, "%c\n", &order, sizeof(order));
	fscanf_s(fp, "%d %d\n", &m, &n);
	(*p) = create(m, n);
	makeList(fp, order, p);
}
polyPointer create(int coefficient, int exponent) {
	polyPointer newNode;
	MALLOC(newNode, sizeof(*newNode));
	newNode->coef = coefficient; newNode->expon = exponent;
	newNode->link = NULL;

	return newNode;
}
void makeList(FILE* fp, char order, polyPointer* pointer) {
	int m, n;
	polyPointer reader = (*pointer);
	while (!feof(fp)) {
		fscanf_s(fp, "%d %d\n", &m, &n);
		polyPointer newNode = create(m, n);
		if (order == 'a') {
			newNode->link = *pointer;
			*pointer = newNode;
		}
		else {
			reader->link = newNode;
			reader = newNode;
			reader->link = NULL;
		}
	}
}
polyPointer padd(polyPointer a, polyPointer b) {
	polyPointer c, rear, temp;
	int sum;
	MALLOC(rear, sizeof(*rear));
	c = rear;
	while (a && b) {
		switch (COMPARE(a->expon, b->expon)) {
			case -1:
				attach(b->coef, b->expon, &rear);
				b = b->link;
				break;
			case 0:
				sum = a->coef + b->coef;
				if (sum) {
					attach(sum, a->expon, &rear);
				}
				a = a->link; b = b->link;
				break;
			case 1:
				attach(a->coef, a->expon, &rear);
				a = a->link;
				break;
		}
	}
	for (; a; a = a->link) {
		attach(a->coef, a->expon, &rear);
	}
	for (; b; b = b->link) {
		attach(b->coef, b->expon, &rear);
	}
	rear->link = NULL;
	temp = c; c = c->link; free(temp);
	return c;
}
void attach(float coefficient, int exponent, polyPointer* pointer) {
	polyPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->coef = coefficient;
	temp->expon = exponent;
	(*pointer)->link = temp;
	*pointer = temp;
}
void printList(polyPointer p) {
	for (; p; p = p->link) {
		printf("(%p : %s%dx^%d : %p) \n", p, (p->coef > 0 ?  "+" : ""), p->coef, p->expon, p->link);
	}
	printf("\n");
}
void deleteList(polyPointer* p) {
	while((*p)) {
		polyPointer temp;
		temp = (*p);
		(*p) = (*p)->link;
		free(temp);
	}
}