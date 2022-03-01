#define MAX(a,b) (((a) > (b)) ? (a) : (b))

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_DEGREE 101

typedef struct {
	int degree;
	float coef[MAX_DEGREE];
}Polynomial;

Polynomial* Zero(void);

float* inputList(void);
void outputList(int d, float list[]);
Polynomial add(Polynomial A, Polynomial B);

int main(void) {

	Polynomial A, B, C;
	C = *Zero();

	printf("<< C(x) = A(x) + B(x) >>\n");
	
	printf("Input the degree of items of A(x) : ");
	scanf_s("%d", &A.degree);

	printf("Input the coefficients A(x) : ");
	
	float* list = inputList();
	for (int i = 0; i <= A.degree; i++) {
		A.coef[i] = list[i];
	}
	
	printf("Input the degree of items of B(x) : ");
	scanf_s("%d", &B.degree);

	printf("Input the coefficients B(x) : ");

	list = inputList();
	for (int i = 0; i <= B.degree; i++) {
		B.coef[i] = list[i];
	}

	C = add(A, B);
	printf("A(X) = ");
	outputList(A.degree, A.coef);
	printf("B(X) = ");
	outputList(B.degree, B.coef);
	printf("C(X) = ");
	outputList(C.degree, C.coef);
	
	return 0;
}
Polynomial* Zero(void) {
	Polynomial z;
	z.degree = 0;
	for (int i = 0; i < MAX_DEGREE; i++) {
		z.coef[i] = 0;
	}
	return &z;
}
float* inputList(void) {

	float* a = malloc(MAX_DEGREE * sizeof(float));
	char num[100];

	getchar();
	gets_s(num, sizeof(num));

	char* str2 = NULL;
	char* temp = strtok_s(num, " ", &str2);
	int i = 0;
	while (temp != NULL) {
		a[i] = atof(temp);
		i++;
		temp = strtok_s(NULL, " ", &str2);
	}
	return a;
}
void outputList(int d, float list[]) {
	for (int i = 0; i < d; i++) {
		printf("%.1fx^%d + ", list[i], (d - i));
	}
	printf("%.1f \n", list[d]);
}
Polynomial add(Polynomial A, Polynomial B){
	Polynomial D;
	int Anum = 0, Bnum = 0, Dnum = 0;
	int degree_a = A.degree;
	int degree_b = B.degree;
	D.degree = MAX(A.degree, B.degree);

	while (Anum <= A.degree && Bnum <= B.degree) {
		if (degree_a > degree_b) {
			D.coef[Dnum++] = A.coef[Anum++];
			degree_a--;
		}
		else if (degree_a == degree_b) {
			D.coef[Dnum++] = A.coef[Anum++] + B.coef[Bnum++];
			degree_a--;
			degree_b--;
		}
		else {
			D.coef[Dnum++] = B.coef[Bnum++];
			degree_b--;
		}
	}
	return D;
}