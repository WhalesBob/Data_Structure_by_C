// 다항식을 아래와 같이 표현하는 방식으로 이용해, 두 다항식을 입력받아 더한 후 그 결과를 출력하는 프로그램을 작성하라. 

#define MAX_TERMS 100
#define COMPARE(x,y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	float coef;
	int expon;
}TERM;

void attach(float coefficient, int exponent);
void padd(int startA, int finishA, int startB, int finishB, int* startD, int* finishD);
void input(int a, int b);
void outputList(int start, int finish);

TERM terms[MAX_TERMS];
int avail = 0;

int main(void) {
	int z1 = 0, z2 = 0;
	int a,b;
	int startA = 0, finishA, startB, finishB;
	int* startD = &z1, * finishD = &z2;
	
	printf("<< D(X) = A(X) + B(X) >> \n");

	printf("Input the number of items of A(X) : ");
	scanf_s("%d", &a);

	finishA = startA + a - 1;
	startB = finishA + 1;

	printf("Input the number of items of B(X) : ");
	scanf_s("%d", &b);

	finishB = startB + b - 1;
	avail = finishB + 1;

	printf("\nInput in descending order\n\n");
	printf("coefficient and exponent of A(X) = 10x^5 + 8x^3 + 7 (10 5, 8 3, 7 0) :");
	for (int i = startA; i <= finishA; i++) {
		scanf_s("%f %d,", &terms[i].coef, &terms[i].expon);
	}

	printf("coefficient and exponent of B(X) = 10x^5 + 8x^2 + 3 (10 5, 8 2, 3 0) :");
	for (int i = startB; i <= finishB; i++){
		scanf_s("%f %d,", &terms[i].coef, &terms[i].expon);
	}
		
	printf("\nA(x) = ");
	outputList(startA, finishA);
	printf("B(x) = ");
	outputList(startB, finishB);

	padd(startA, finishA, startB, finishB,startD,finishD);
	printf("D(x) = ");
	outputList(*startD, *finishD);
	return 0;
}
void attach(float coefficient, int exponent) {
	if (avail >= MAX_TERMS) {
		fprintf(stderr, "Too many terms in the polynomials");
		exit(EXIT_FAILURE);
	}
	terms[avail].coef = coefficient;
	terms[avail++].expon = exponent;
}
void padd(int startA, int finishA, int startB, int finishB, int* startD, int* finishD) {
	float coefficient;
	*startD = avail;
	while (startA <= finishA && startB <= finishB) {
		switch COMPARE(terms[startA].expon, terms[startB].expon) {
			case -1 :
				attach(terms[startB].coef, terms[startB].expon);
				startB++;
				break;
			case 0:
				coefficient = terms[startA].coef + terms[startB].coef;
				if (coefficient) {
					attach(coefficient, terms[startA].expon);
					startA++;
					startB++;
				}
				break;
			case 1:
				attach(terms[startA].coef, terms[startA].expon);
				startA++;
		}
	}
	for (; startA <= finishA; startA++) {
		attach(terms[startA].coef, terms[startA].expon);
	}
	for (; startB <= finishB; startB++) {
		attach(terms[startB].coef, terms[startB].expon);
	}
	*finishD = avail - 1;
}
void outputList(int start,int finish) {
	for (int i = start; i < finish; i++) {
		printf("%.1fx^%d + ", terms[i].coef, terms[i].expon);
	}
	
	if (terms[finish].expon == 0) {
		printf("%.1f \n", terms[finish].coef);
	}
	else {
		printf("%.1fx^%d \n", terms[finish].coef, terms[finish].expon);
	}
}