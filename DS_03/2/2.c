#define MALLOC(p,s){\
	if(!((p) = malloc(s))){\
		fprintf(stderr,"Insufficient Memory");\
		exit(EXIT_FAILURE);\
	}\
}\

#include <stdio.h>
#include <stdlib.h>

int** make2DArray(rows, cols);

int main(void) {

	int** ipp;
	int rows, cols;
	printf("이차원 배열의 행과 열의 수를 입력 하세요 : ");
	scanf_s("%d %d", &rows, &cols);
	ipp = make2DArray(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("ipp[%d][%d] = %d ", i,j, ipp[i][j]);
		}
		printf("\n");
	}
	return 0;
}

int** make2DArray(rows, cols) {
	int** x;
	MALLOC(x, rows * sizeof(*x));

	for (int i = 0; i < rows; i++) {
		MALLOC(x[i], cols * sizeof(**x));
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			x[i][j] = rand() % 100;
		}
	}
	return x;
}