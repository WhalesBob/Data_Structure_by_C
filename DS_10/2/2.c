/*
2. 다음과 같이 헤더노드를 가진 단일 환형연결리스트 (singly linked circular list)을 이용한
다항식 더하기 프로그램을 작성하라.

(1) 실행 순서
① 입력파일(“a.txt,” “b.txt”)로부터 데이터를 입력받아서 두 개의 다항식 a, b를 각각 헤더노드를
가진 단일 환형연결리스트 형태로 구현하고, 두 다항식을 더하시오. 더한 결과도 역시
헤더노드를 가진 단일 환형연결리스트 형태로 구현하시오. 
그리고 빈 노드를 관리하는 avail 리스트에 리스트 a, b, c 순으로 반환한 후 avail 리스트를 운영체제에 반환하시오.
② a, b 두 다항식의 정보를 출력한다. 
③ a+b의 결과를 c에 저장하는 다항식 더하기를 수행한다. ④ 다항식 c를 출력한다. 
⑤ 다항식 a, b, c를 avail 에 반납한다. 
⑥ avail 리스트를 출력한다. ⑦ avail을 삭제한다.
*/

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
polyPointer avail = NULL;

void makeWholeList(FILE* fp, polyPointer* p);
polyPointer getNode(void);
void returnNode(polyPointer node);
polyPointer create(int coefficient, int exponent);
void makeList(FILE* fp, char order, polyPointer* pointer);
polyPointer padd(polyPointer a, polyPointer b);
void attach(float coefficient, int exponent, polyPointer* pointer);
void printList(polyPointer p);
void deleteList(polyPointer* p, polyPointer* newAvail);
polyPointer invert(polyPointer lead);
polyPointer concatenate(polyPointer p1, polyPointer p2);
void deleteAll(polyPointer* avail);

int main(void) {

	FILE* fp1, * fp2;
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

	polyPointer newAvail1, newAvail2;
	deleteList(&a,&newAvail1);
	deleteList(&b,&newAvail2);
	newAvail1 = concatenate(newAvail2, newAvail1);
	deleteList(&sum,&newAvail2);
	newAvail1 = concatenate(newAvail2, newAvail1);

	printf("avail : \n");
	printList(newAvail1);

	deleteAll(newAvail1);
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
polyPointer getNode(void) {
	polyPointer node;
	if (avail) {
		node = avail;
		avail = avail->link;
	}
	else {
		MALLOC(node, sizeof(*node));
	}
	return node;
}
void returnNode(polyPointer node) {
	node->link = avail;
	avail = node;
}
polyPointer create(int coefficient, int exponent) {
	polyPointer newNode = getNode();
	newNode->coef = coefficient; newNode->expon = exponent;
	newNode->link = NULL;

	return newNode;
}
void makeList(FILE* fp, char order, polyPointer* pointer) {

	polyPointer first = getNode();
	first->expon = -1;

	int m, n;
	polyPointer reader = (*pointer); // 오름차순일 때, reader는 맨 뒤에 있다. 그리고 pointer는 맨 앞에 있다.
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
		}
	}
	reader->link = first;
	first->link = (*pointer);
	(*pointer) = first;
}
polyPointer padd(polyPointer a, polyPointer b) {
	polyPointer startA, c, lastC;
	int sum, done = 0;
	startA = a;
	a = a->link;
	b = b->link;
	c = getNode();
	c->expon = -1; lastC = c;
	do {
		switch (COMPARE(a->expon, b->expon)) {
			case -1 :
				attach(b->coef, b->expon, &lastC);
				b = b->link;
				break;
			case 0 :
				if (startA == a) {
					done = 1;
				}
				else {
					sum = a->coef + b->coef;
					if (sum) {
						attach(sum, a->expon, &lastC);
					}
					a = a->link; b = b->link;
				}
				break;
			case 1 :
				attach(a->coef, a->expon, &lastC);
				a = a->link;
				break;
		}
	} while (!done);
	lastC->link = c;
	return c;
}
void attach(float coefficient, int exponent, polyPointer* pointer) {
	polyPointer temp = getNode();
	temp->coef = coefficient;
	temp->expon = exponent;
	(*pointer)->link = temp;
	*pointer = temp;
}
void printList(polyPointer p) {
	polyPointer start = p;
	
	do {
		printf("(%p : %s%dx^%d : %p) \n", p, (p->coef > 0 ? "+" : ""), p->coef, p->expon, p->link);
		p = p->link;
	} while (p != start);
	printf("\n");
}
void deleteList(polyPointer* p,polyPointer * newAvail) {

	polyPointer temp = (*p)->link ,start = (*p);
	(*p) = (*p)->link;
	start->link = NULL;
	do {
		temp = (*p);
		(*p) = (*p)->link;
		returnNode(temp);
	} while (temp != start);

	(*newAvail) = invert(avail);
	avail = NULL;
}
polyPointer invert(polyPointer lead){
	polyPointer middle, trail;
	middle = NULL;
	while (lead) {
		trail = middle;
		middle = lead;
		lead = lead->link;
		middle->link = trail;
	}
	return middle;
}
polyPointer concatenate(polyPointer p1, polyPointer p2) {
	polyPointer temp;
	if (!p1) { return p2; }
	if (!p2) { return p1; }

	for (temp = p1; temp->link; temp = temp->link);
	temp->link = p2;

	return p1;
}
void deleteAll(polyPointer* avail) {
	polyPointer temp;
	while ((*avail)) {
		temp = *avail;
		(*avail) = (*avail)->link;
		free(temp);
	}
}